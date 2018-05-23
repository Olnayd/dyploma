#include "CCourseCtrl.h"

#include <map>
#include <QFileInfo>
#include <QDir>
#include "database/connection/EStorage.h"
#include "database/connection/CDatabaseConnectionFactory.h"
#include <QDebug>

CCourseCtrl::CCourseCtrl( )
    : mSqlController   ( std::make_shared<CSqlSubController>())
    , mTextController  ( std::make_shared<CTextStorageSubCtrl>(mSqlController))
    , mImageController ( std::make_shared<CImageStorageSubCtrl>(mSqlController))
{
    addSubCtrl(std::static_pointer_cast<common::controller::CSubController>(mSqlController));
    addSubCtrl(std::static_pointer_cast<common::controller::CSubController>(mTextController));
    addSubCtrl(std::static_pointer_cast<common::controller::CSubController>(mImageController));

}

bool CCourseCtrl::init()
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
            this,         SLOT(slotNewConnection()));
    return true;
}

const char* CCourseCtrl::getName()
{
    return "CourseCtrl";
}

bool CCourseCtrl::prepareShutdown()
{
    return true;
}


/*virtual*/ void CCourseCtrl::slotNewConnection()
{
    QTcpSocket* pClientSocket = m_ptcpServer->nextPendingConnection();
    connect(pClientSocket, SIGNAL(disconnected()),
            pClientSocket, SLOT(deleteLater()));

    connect(pClientSocket, SIGNAL(readyRead()),
            this,          SLOT(slotReadClient()));

    sendToClient(pClientSocket, "Server Response: Connected!");
}

// ----------------------------------------------------------------------
void CCourseCtrl::slotReadClient()
{
    QTcpSocket* pClientSocket = (QTcpSocket*)sender();
    QDataStream in(pClientSocket);
    in.setVersion(QDataStream::Qt_5_3);
    if (!m_nNextBlockSize) {

        in >> m_nNextBlockSize;
    }


    QTime   time;
    QString str;
    in >> time >> str;

    QString strMessage =
            time.toString() + " " + "Client has sent - " + str;
    m_ptxt->append(strMessage);

    m_nNextBlockSize = 0;

    sendToClient(pClientSocket,
                 "Server Response: Received \"" + str + "\""
                 );
}

// ----------------------------------------------------------------------
void CCourseCtrl::sendToClient(QTcpSocket* pSocket, const QString& str)
{
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_3);
    out << quint16(0) << QTime::currentTime() << str;

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    pSocket->write(arrBlock);
}
