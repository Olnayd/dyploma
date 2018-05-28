#include "CCourseProcessor.hpp"

#include <QDataStream>
#include"RequestType.hpp"
#include"ResponseType.hpp"

quint32 getClientId()
{
    static quint32 next_client_id = 1;
    return next_client_id++;
}

quint32 getSequenceId()
{
    static quint32 sequenceID = 0;
    return ++sequenceID;
}

void fillCommonInfoForResponse(QDataStream& dataStream, const CResponseContext& responseContext)
{
    dataStream << responseContext.responseId << responseContext.seqId ;
}

void fillCommonInfoForError(QDataStream& dataStream, const quint32 error, const CResponseContext& responseContext)
{
    dataStream << (quint32)Response_Unknown << responseContext.seqId << error;
}

ResponseType getResponse(const RequestType requestType)
{
    switch(requestType)
    {
    case Request_SignIn: return Response_SignIn;
    case Request_SignUp: return Response_SignUp;
    case Request_GetCourseInfo: return Response_GetCourseInfo;
    default:                   return Response_Unknown;
    }
}

CCourseProcessor::CCourseProcessor()
    : m_ptcpServer (nullptr)
    , m_nNextBlockSize(0)
{
}

bool CCourseProcessor::start()
{
    if (m_ptcpServer == nullptr)
    {
        m_ptcpServer = new QTcpServer(this);
        if (!m_ptcpServer->listen(QHostAddress::Any, 22525)) {
            qDebug() << m_ptcpServer->errorString();
            m_ptcpServer->close();
            return false;
        }
        connect(m_ptcpServer, SIGNAL(newConnection()),
                this,         SLOT(slotNewConnection())
               );
    }
    qDebug()<< "CCM :: stated";
    return true;
}

void CCourseProcessor::slotNewConnection()
{
    quint32 clientId = getClientId();
    auto insertResult = mClientList.insert(std::make_pair(clientId, std::make_shared<CNetworkClient>(m_ptcpServer->nextPendingConnection(), clientId)));

    if(insertResult.second)
    {
        auto client = (*(insertResult.first)).second;

        connect(client.get(), SIGNAL(disconnected()),
                this, SLOT(slotRemoveConnection()));

        connect(client.get(), SIGNAL(disconnected()),
                this, SLOT(deleteLater()));

        connect(client.get(), SIGNAL(readyRead()),
                this,   SLOT(slotReadClient()));
    }
}

void CCourseProcessor::slotRemoveConnection()
{
    CNetworkClient* pClient = (CNetworkClient*)sender();
    auto it = mClientList.find(pClient->getClientId());
    if (it != mClientList.end())
            mClientList.erase(it);
}

// ----------------------------------------------------------------------
void CCourseProcessor::slotReadClient()
{
    CNetworkClient* pClient = (CNetworkClient*)sender();

    quint32 clientId = pClient->getClientId();
    QTcpSocket* pClientSocket = pClient->getSocket();

    QDataStream in(pClientSocket);
    for(;;){
        if (!m_nNextBlockSize) {
            if (pClientSocket->bytesAvailable() < sizeof(quint16)) {
                break;
            }
            in >> m_nNextBlockSize;
            qDebug()<< m_nNextBlockSize;
        }
        if (pClientSocket->bytesAvailable() < m_nNextBlockSize) {
            break;
        }

        quint32 seqId;
        quint32 requestId;

        in >> requestId;
        seqId = getSequenceId();
        sendToClient(pClientSocket, requestId, seqId);
        CResponseContext responseContext(mClientList.find(clientId)->second, getResponse(static_cast<RequestType>(requestId)), seqId);

        switch (requestId) {
        case Request_SignIn:
        {
            ClientIdentificator clientIdent;
            in >> clientIdent;
            qDebug()<< "CCM :: SingIn( <" + clientIdent.login + ", " + clientIdent.password + "> )";
            signIn(clientIdent, responseContext);
        } break;
        case Request_SignUp:
        {
            ClientIdentificator clientIdent;
            ClientInformation clientInfo;
            in >> clientIdent >> clientInfo;
            qDebug()<< "CCM :: SingIn( <" + clientIdent.login
                                          + ", " + clientIdent.password
                                          + ">, <" + clientInfo.name
                                          + ", " + clientInfo.address
                                          + ", " + clientInfo.email
                                          + ", " + clientInfo.phone_number
                                          + ", " + clientInfo.address
                                          + "> )";
            signUp(clientIdent, clientInfo, responseContext);
        } break;
        case Request_GetCourseInfo:
        {
            quint32 courseId;
            in >> courseId;
            qDebug()<< "CCM :: getCourseInfo( " + QString::number(courseId) + " )";
            getCourseInfo(courseId, responseContext);
        } break;
        default:
            break;
        }

        m_nNextBlockSize = 0;

    }




}

// ----------------------------------------------------------------------
void CCourseProcessor::sendToClient(QTcpSocket* pSocket, const quint32 requestid, const quint32 sequenceId)
{
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_3);
    out << quint16(0) << requestid << sequenceId;
        quint32 sequence;
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    pSocket->write(arrBlock);
}

/////responses

void CCourseProcessor::response_signUp(const bool result, const CResponseContext& responseContext)
{
    if ( responseContext.responseId != (quint32)Response_SignUp ) ; //TODO: alarn

    auto it = mClientList.find(responseContext.clientPtr->getClientId());
    if (it != mClientList.end())
    {
        QTcpSocket* pClientSocket = it->second->getSocket();
        QByteArray  arrBlock;
        QDataStream out(&arrBlock, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_3);
        out << quint16(0);

        fillCommonInfoForResponse(out, responseContext);

        out << result;
        out.device()->seek(0);
        out << quint16(arrBlock.size() - sizeof(quint16));
        pClientSocket->write(arrBlock);
    }
}

void CCourseProcessor::response_signIn(const ClientInformation& clientInfo, const CResponseContext& responseContext)
{
    if ( responseContext.responseId != (quint32)Response_SignIn ) ; //TODO: alarn

    auto it = mClientList.find(responseContext.clientPtr->getClientId());
    if (it != mClientList.end())
    {
        QTcpSocket* pClientSocket = it->second->getSocket();
        QByteArray  arrBlock;
        QDataStream out(&arrBlock, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_3);
        out << quint16(0);

        fillCommonInfoForResponse(out, responseContext);

        out << clientInfo;
        out.device()->seek(0);
        out << quint16(arrBlock.size() - sizeof(quint16));
        pClientSocket->write(arrBlock);
    }
}

void CCourseProcessor::response_getCourseInfo(const CResponseContext& responseContext)
{
    auto it = mClientList.find(responseContext.clientPtr->getClientId());
    if (it != mClientList.end())
    {
        QTcpSocket* pClientSocket = it->second->getSocket();
        QByteArray  arrBlock;
        QDataStream out(&arrBlock, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_3);
        out << quint16(0);

        fillCommonInfoForResponse(out, responseContext);

        out.device()->seek(0);
        out << quint16(arrBlock.size() - sizeof(quint16));
        pClientSocket->write(arrBlock);
    }
}

void CCourseProcessor::response_error(const quint32 error, const CResponseContext& responseContext)
{
    auto it = mClientList.find(responseContext.clientPtr->getClientId());
    if (it != mClientList.end())
    {
        QTcpSocket* pClientSocket = it->second->getSocket();
        QByteArray  arrBlock;
        QDataStream out(&arrBlock, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_3);
        out << quint16(0);

        fillCommonInfoForError(out, error, responseContext);

        out.device()->seek(0);
        out << quint16(arrBlock.size() - sizeof(quint16));
        pClientSocket->write(arrBlock);
    }
}
