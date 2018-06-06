#ifndef CTEXTSTORAGESUBCTRL_H
#define CTEXTSTORAGESUBCTRL_H

#include "common/controller/CSubController.h"
#include "controller/subController/CSqlSubCtrl.h"
#include "network/processor/course/types/CourseListWorkingType.hpp"
#include "network/processor/course/types/CourseListFilter.hpp"
#include "network/processor/course/types/LectionInformation.hpp"
#include "network/processor/course/ICourseResponseHandle.hpp"

class CTextStorageSubCtrl : public common::controller::CSubController
{
public:
    CTextStorageSubCtrl(std::shared_ptr<CSqlSubCtrl> sqlController);
    virtual bool init() override final;
    virtual const char* getName() override final;
    virtual bool prepareShutdown() override final;

    void getTopicList(const CResponseContext& responseContext, ICourseResponseHandle& reponseHandle);
    void getCourseListByFilter( const qint32 clientdatabaseid, const CourseListWorkingType workType, const CourseListFilter& filter, const CResponseContext& responseContext, ICourseResponseHandle& reponseHandle);

    void getLection( const qint32 clientdatabaseid, const quint32 lectionId, const CResponseContext& responseContext, ICourseResponseHandle& reponseHandle);
    void getLectionPreviewList(const quint32 courseid, const CResponseContext& responseContext, ICourseResponseHandle& reponseHandle);



    void subscribeOnCourse(const qint32 clientdatabaseid, const quint32 courseid, const CResponseContext& responseContext, ICourseResponseHandle& reponseHandle);
    void createCourse( const qint32 clientdatabaseid, const Course& courseInfo, const CResponseContext& responseContext, ICourseResponseHandle& reponseHandle);
    void createLection( const qint32 clientdatabaseid, const quint32 courseid, const LectionInformation& courseInfo, const CResponseContext& responseContext, ICourseResponseHandle& reponseHandle);

private:
    std::shared_ptr<CSqlSubCtrl> mSqlController;
};

#endif // CTEXTSTORAGESUBCTRL_H
