#include "CCourseProcessore.hpp"

CCourseProcessor::CCourseProcessor(int nPort)
{
    m_ptcpServer = new QTcpServer(this);
    if (!m_ptcpServer->listen(QHostAddress::Any, nPort)) {
        QMessageBox::critical(0,
                              "Server Error",
                              "Unable to start the server:"
                              + m_ptcpServer->errorString()
                             );
        m_ptcpServer->close();
        return;
    }
    connect(m_ptcpServer, SIGNAL(newConnection()),
            this,         SLOT(slotNewConnection())
           );
}

void CCourseProcessor::slotNewConnection()
{
    CClient client(m_ptcpServer->nextPendingConnection());
    QTcpSocket* pClientSocket = m_ptcpServer->nextPendingConnection();

    connect(client, SIGNAL(disconnected()),
            client, SLOT(deleteLater()));

    connect(client, SIGNAL(readyRead()),
            this,   SLOT(slotReadClient()));



    sendToClient(pClientSocket, "Server Response: Connected!");
}

// ----------------------------------------------------------------------
void CCourseProcessor::slotReadClient()
{
    CClient* pClient = (CClient*)sender();
    QTcpSocket* pClientSocket = pClient->getSocket();
    QDataStream in(pClientSocket);
    in.setVersion(QDataStream::Qt_5_3);
    for(;;){
        if (!m_nNextBlockSize) {
            if (pClientSocket->bytesAvailable() < sizeof(quint16)) {
                break;
            }
            in >> m_nNextBlockSize;
        }
        if (pClientSocket->bytesAvailable() < m_nNextBlockSize) {
            break;
        }

        quint32 requestPOS;
        qint32 requestId;

        in >> requestId;

        switch (requestId) {
        case 1:
        {
            QString login;
            QString passw;

            in >> login >> passw;

            //todo create request
            //todo add request in queu
            //return id request ot client
            std::make_tuple(login, password);
        }
            break;
        case 2:
        {
            QString something;
            in >> something;
        }
            break;
        default:
            break;
        }

        m_nNextBlockSize = 0;

        sendToClient(pClientSocket,
                     "Server Response: Received \"" + str + "\""
                    );
    }




}

// ----------------------------------------------------------------------
void CCourseProcessor::sendToClient(QTcpSocket* pSocket, const QString& str)
{
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_3);
    out << quint16(0) << QTime::currentTime() << str;

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    pSocket->write(arrBlock);
}
