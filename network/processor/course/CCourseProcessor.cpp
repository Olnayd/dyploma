#include "CCourseProcessor.hpp"

#include <QDataStream>
#include"types/RequestType.hpp"
#include"types/ResponseType.hpp"

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

void fillCommonInfoForError(QDataStream& dataStream, const ErrorType error, const CResponseContext& responseContext)
{
    dataStream << (quint32)Response_Unknown << responseContext.seqId << error;
}

ResponseType getResponse(const RequestType requestType)
{
    switch(requestType)
    {
    case Request_SignIn:                return Response_SignIn;
    case Request_SignUp:                return Response_SignUp;
    case Request_GetTopicList:          return Response_GetTopicList;
    case Request_GetCourseList:         return Response_GetCourseList;
    case Request_GetCourseListByFilter: return Response_GetCourseList;
    case Request_CreateCourse:          return Response_CreateCourse;
    case Request_CreateLection:         return Response_CreateLection;
    case Request_SubscribeOnCourse:     return Response_SubscribeOnCourse;
    case Request_GetLectionPreviewList: return Response_GetPreviewLectionList;
    case Request_GetLection:            return Response_GetLection;
    default:                            return Response_Unknown;
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
        case Request_GetLectionPreviewList:
        {
            quint32 courseId;
            in >> courseId;
            qDebug()<< "CCM :: getLectionPreviewList( " + QString::number(courseId) + " )";
            getLectionPreviewList(courseId, responseContext);

        } break;

        case Request_GetLection:
        {
            quint32 lectionId;
            in >> lectionId;
            qDebug()<< "CCM :: getLection( " + QString::number(lectionId) + " )";
            getLection(lectionId, responseContext);

        } break;

        case Request_CreateLection:
        {
            quint32 courseId;
            LectionInformation lectionInfo;
            in >> courseId >> lectionInfo;
            qDebug()<< "CCM :: createLection( <" + lectionInfo.name
                                                 + ", " + lectionInfo.description + "> )";
            createLection(courseId, lectionInfo, responseContext);
        } break;

        case Request_CreateCourse:
        {
            Course courseInfo;
            in >> courseInfo;
            qDebug()<< "CCM :: createCourse( <"  + courseInfo.name
                                                 + ", " + courseInfo.description + "> )";
            createCourse(courseInfo, responseContext);
        } break;
        case Request_SubscribeOnCourse:
        {
            quint32 courseId;
            in >> courseId;
            qDebug()<< "CCM :: subscribeOnCourse( " + QString::number(courseId) + " )";
            subscribeOnCourse(courseId, responseContext);

        } break;

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
            qDebug()<< "CCM :: SingUp( <" + clientIdent.login
                                          + ", " + clientIdent.password
                                          + ">, <" + clientInfo.name
                                          + ", " + clientInfo.address
                                          + ", " + clientInfo.email
                                          + ", " + clientInfo.phone_number
                                          + ", " + clientInfo.address
                                          + "> )";
            signUp(clientIdent, clientInfo, responseContext);
        } break;
        case Request_GetTopicList:
        {
            qDebug()<< "CCM :: getTopicList( )";
            getTopicList(responseContext);
        } break;
        case Request_GetCourseListByFilter:
        {
            CourseListWorkingType workType;
            CourseListFilter filter;
            in >> workType >> filter;
            qDebug()<< "CCM :: getCourseListByFilter( " + QString::number((quint32)workType)
                                                        + ", <" + QString::number((quint32)filter.filterType)
                                                        + ","   + QString::number(filter.id)
                                                        + ">)";
            getCourseListByFilter(workType, filter, responseContext);

        } break;


        case Request_GetCourseList:
        {
            CourseListWorkingType workType;
            in >> workType;
            qDebug()<< "CCM :: getCourseList( " + QString::number((quint32)workType) + " )";
            getCourseList(workType, responseContext);
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
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    pSocket->write(arrBlock);
}

/////responses

/*virtual*/ void CCourseProcessor::response_getLection( const LectionInformation& lection, const CResponseContext& responseContext )
{
    //if ( responseContext.responseId != (quint32)Response_SubscribeOnCourse ) ; //TODO: alarm

    auto it = mClientList.find(responseContext.clientPtr->getClientId());
    if (it != mClientList.end())
    {
        QTcpSocket* pClientSocket = it->second->getSocket();
        QByteArray  arrBlock;
        QDataStream out(&arrBlock, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_3);
        out << quint16(0);

        fillCommonInfoForResponse(out, responseContext);

        out << lection;
        out.device()->seek(0);
        out << quint16(arrBlock.size() - sizeof(quint16));
        pClientSocket->write(arrBlock);
    }
}

/*virtual*/ void CCourseProcessor::response_getLectionPreviewList( const QVector<LectionPreview>& lectionList, const CResponseContext& responseContext )
{
    //if ( responseContext.responseId != (quint32)Response_SubscribeOnCourse ) ; //TODO: alarm

    auto it = mClientList.find(responseContext.clientPtr->getClientId());
    if (it != mClientList.end())
    {
        QTcpSocket* pClientSocket = it->second->getSocket();
        QByteArray  arrBlock;
        QDataStream out(&arrBlock, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_3);
        out << quint16(0);

        fillCommonInfoForResponse(out, responseContext);

        out << lectionList;
        out.device()->seek(0);
        out << quint16(arrBlock.size() - sizeof(quint16));
        pClientSocket->write(arrBlock);
    }
}

/*virtual*/ void CCourseProcessor::response_subscribeOnCourse(const bool result, const CResponseContext& responseContext)
{
    //if ( responseContext.responseId != (quint32)Response_SubscribeOnCourse ) ; //TODO: alarm

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

/*virtual*/ void CCourseProcessor::response_createCourse( const quint32 courseid, const CResponseContext& responseContext)
{
    //if ( responseContext.responseId != (quint32)Response_CreateLection ) ; //TODO: alarm

    auto it = mClientList.find(responseContext.clientPtr->getClientId());
    if (it != mClientList.end())
    {
        QTcpSocket* pClientSocket = it->second->getSocket();
        QByteArray  arrBlock;
        QDataStream out(&arrBlock, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_3);
        out << quint16(0);

        fillCommonInfoForResponse(out, responseContext);

        out << courseid;
        out.device()->seek(0);
        out << quint16(arrBlock.size() - sizeof(quint16));
        pClientSocket->write(arrBlock);
    }
}

/*virtual*/ void CCourseProcessor::response_createLection(const quint32 lectionId, const CResponseContext& responseContext)
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

        out << lectionId;
        out.device()->seek(0);
        out << quint16(arrBlock.size() - sizeof(quint16));
        pClientSocket->write(arrBlock);
    }
}

///*virtual*/ void CCourseProcessor::response_createTest(const quint32 testId, const CResponseContext& responseContext)
//{
//    auto it = mClientList.find(responseContext.clientPtr->getClientId());
//    if (it != mClientList.end())
//    {
//        QTcpSocket* pClientSocket = it->second->getSocket();
//        QByteArray  arrBlock;
//        QDataStream out(&arrBlock, QIODevice::WriteOnly);
//        out.setVersion(QDataStream::Qt_5_3);
//        out << quint16(0);

//        fillCommonInfoForResponse(out, responseContext);

//        out << testId;
//        out.device()->seek(0);
//        out << quint16(arrBlock.size() - sizeof(quint16));
//        pClientSocket->write(arrBlock);
//    }
//}


void CCourseProcessor::response_getTopicList(const QVector<CourseTopic> &topicList, const CResponseContext &responseContext)
{
    //if ( responseContext.responseId != (quint32)Response_GetTopicList ) ; //TODO: alarm

    auto it = mClientList.find(responseContext.clientPtr->getClientId());
    if (it != mClientList.end())
    {
        QTcpSocket* pClientSocket = it->second->getSocket();
        QByteArray  arrBlock;
        QDataStream out(&arrBlock, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_3);
        out << quint16(0);

        fillCommonInfoForResponse(out, responseContext);

        out << topicList;
        out.device()->seek(0);
        out << quint16(arrBlock.size() - sizeof(quint16));
        pClientSocket->write(arrBlock);
    }
}

void CCourseProcessor::response_getCourseList( const QVector<Course>& courseList, const CResponseContext& responseContext)
{
    //if ( responseContext.responseId != (quint32)Response_GetCourseList ) ; //TODO: alarm

    auto it = mClientList.find(responseContext.clientPtr->getClientId());
    if (it != mClientList.end())
    {
        QTcpSocket* pClientSocket = it->second->getSocket();
        QByteArray  arrBlock;
        QDataStream out(&arrBlock, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_3);
        out << quint16(0);

        fillCommonInfoForResponse(out, responseContext);

        out << courseList;
        out.device()->seek(0);
        out << quint16(arrBlock.size() - sizeof(quint16));
        pClientSocket->write(arrBlock);
    }
}

void CCourseProcessor::response_signUp(const bool result, const CResponseContext& responseContext)
{
    //if ( responseContext.responseId != (quint32)Response_SignUp ) ; //TODO: alarn

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
    //if ( responseContext.responseId != (quint32)Response_SignIn ) ; //TODO: alarn

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

void CCourseProcessor::response_error(const ErrorType error, const CResponseContext& responseContext)
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
