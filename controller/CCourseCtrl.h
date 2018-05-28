#ifndef CCOURSECTRL_H
#define CCOURSECTRL_H

#include <map>
#include "database/connection/EStorage.h"
#include "common/controller/CController.h"
#include "subController/CSqlSubCtrl.h"
#include "subController/CImageStorageSubCtrl.h"
#include "subController/CTextStorageSubCtrl.h"
#include "subController/CUserSubCtrl.h"
#include "network/processor/course/CCourseProcessor.hpp"
#include <QTcpServer>

class QTcpServer;
class QTcpSocket;

class CCourseCtrl
        : public common::controller::CController
        , public CCourseProcessor

{
public:
    CCourseCtrl();

    bool init() override;
    bool prepareShutdown() override;
    const char* getName() override;

public:
    virtual void getCourseInfo(const quint32 courseId, const CResponseContext &responseContext) override;
    virtual void autorization(const QString& login, const QString& password, const CResponseContext& responseContext) override;

private:
    void sendToClient(QTcpSocket* pSocket, const QString& str);
private:
    QTcpServer* m_ptcpServer;
    std::shared_ptr<CSqlSubCtrl> mSqlController;
    std::shared_ptr<CTextStorageSubCtrl> mTextController;
    std::shared_ptr<CImageStorageSubCtrl> mImageController;
    std::shared_ptr<CUserSubCtrl> mUserController;



};

#endif // CCOURSECTRL_H
