#ifndef CCOURSECTRL_H
#define CCOURSECTRL_H

#include <map>
#include "database/connection/EStorage.h"
#include "common/controller/CController.h"
#include "subController/CSqlSubCtrl.h"
#include "subController/CImageStorageSubCtrl.h"
#include "subController/CTextStorageSubCtrl.h"

#include <QTcpServer>

class QTcpServer;
class QTcpSocket;

class CCourseCtrl :
        public QObject,
        public common::controller::CController
{
    Q_OBJECT
public:
    CCourseCtrl();

    bool init() override;
    bool prepareShutdown() override;
    const char* getName() override;

private:
    void sendToClient(QTcpSocket* pSocket, const QString& str);
private:
    QTcpServer* m_ptcpServer;
    std::shared_ptr<CSqlSubController> mSqlController;
    std::shared_ptr<CTextStorageSubCtrl> mTextController;
    std::shared_ptr<CImageStorageSubCtrl> mImageController;

public slots:
    virtual void slotNewConnection();
            void slotReadClient   ();


};

#endif // CCOURSECTRL_H
