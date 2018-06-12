#ifndef CTEXTSTORAGESUBCTRL_H
#define CTEXTSTORAGESUBCTRL_H

#include "common/controller/CSubController.h"
#include "controller/subController/CSqlSubCtrl.h"
#include "network/processor/course/types/course/CourseListWorkingType.hpp"
#include "network/processor/course/types/course/CourseListFilter.hpp"
#include "network/processor/course/types/lecture/Lecture.hpp"
#include "network/processor/course/types/test/TestUserAnswers.hpp"
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

    void getTest(const qint32 clientdatabaseid, const ClientType clientType, const quint32 lectureId, const CResponseContext& responseContext, ICourseResponseHandle& reponseHandle);
    void getLecture( const qint32 clientdatabaseid, const ClientType clientType, const quint32 lectionId, const CResponseContext& responseContext, ICourseResponseHandle& reponseHandle);
    void getLecturePreviewList(const qint32 clientdatabaseid, const ClientType clientType, const quint32 courseid, const CResponseContext& responseContext, ICourseResponseHandle& reponseHandle);

    void createCourse( const qint32 clientdatabaseid, const Course& courseInfo, const CResponseContext& responseContext, ICourseResponseHandle& reponseHandle);
    void createLecture( const qint32 clientdatabaseid, const quint32 courseid, const Lecture& courseInfo, const CResponseContext& responseContext, ICourseResponseHandle& reponseHandle);
    void createTest(const qint32 clientdatabaseid, const quint32 lectureId, const Test& test, const CResponseContext& responseContext, ICourseResponseHandle& reponseHandle);

    void subscribeOnCourse(const qint32 clientdatabaseid, const quint32 courseid, const CResponseContext& responseContext, ICourseResponseHandle& reponseHandle);

    void finishTest(const qint32 clientdatabaseid, const TestUserAnswers& userAnswears, const CResponseContext& responseContext, ICourseResponseHandle& reponseHandle);
    void finishLecture(const qint32 clientdatabaseid, const quint32 lectureId, const CResponseContext& responseContext, ICourseResponseHandle& reponseHandles);




private:
    QVector<TestQuestion> getTestQuestionFromJson( const QString& jsonQuestions, bool ignoreRightAnswer);
    QString getTestQuestionAsJson( const Test& test);

    qreal getEvaluation( QVector<TestQuestion> questionList, TestUserAnswers userAnswers);
private:
    std::shared_ptr<CSqlSubCtrl> mSqlController;
};

#endif // CTEXTSTORAGESUBCTRL_H
