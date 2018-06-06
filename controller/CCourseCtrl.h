#ifndef CCOURSECTRL_H
#define CCOURSECTRL_H

#include <map>
#include "database/connection/EStorage.h"
#include "common/controller/CController.h"
#include "subController/CSqlSubCtrl.h"
#include "subController/CImageStorageSubCtrl.h"
#include "subController/text/CTextStorageSubCtrl.h"
#include "subController/user/CUserSubCtrl.h"
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
    virtual void getTopicList(const CResponseContext& responseContext) override final;
    virtual void getCourseList( const CourseListWorkingType workType, const CResponseContext& responseContext) override final;
    virtual void getCourseListByFilter( const CourseListWorkingType workType, const CourseListFilter& filter, const CResponseContext& responseContext) override final;

    virtual void getLection(const quint32 lectionId, const CResponseContext& responseContext) override final;
    virtual void getLectionPreviewList(const quint32 courseid, const CResponseContext& responseContext) override final;



    virtual void subscribeOnCourse(const quint32 courseid, const CResponseContext& responseContext) override final;
    virtual void createCourse( const Course& courseInfo, const CResponseContext& responseContext) override final;
    virtual void createLection( const quint32 courseid, const LectionInformation& courseInfo, const CResponseContext& responseContext) override final;



    virtual void signIn(const ClientIdentificator &clientIdent, const CResponseContext &responseContext) override;
    virtual void signUp(const ClientIdentificator &clientIdent, const ClientInformation &clientInfo, const CResponseContext &responseContext) override;
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
