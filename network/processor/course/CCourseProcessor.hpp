#ifndef CCOURSEPROCESSOR_H
#define CCOURSEPROCESSOR_H

#include <memory>
#include <QTcpServer>

#include "ICourseResponseHandle.hpp"
#include "network/CNetworkClient.hpp"
#include "types/course/CourseListWorkingType.hpp"
#include "types/course/CourseListFilter.hpp"
#include "types/lecture/Lecture.hpp"
#include "types/test/TestUserAnswers.hpp"

class CCourseProcessor
        : public QObject
        , public ICourseResponseHandle
{
    Q_OBJECT
public:
    CCourseProcessor();
    bool start();
    //requests
    virtual void signIn(const ClientIdentificator& clientIdent, const CResponseContext& responseContext) = 0;
    virtual void signUp(const ClientIdentificator& clientIdent, const ClientInformation& clientInfo, const CResponseContext& responseContext) = 0;
    virtual void subscribeOnCourse(const quint32 courseid, const CResponseContext& responseContext) = 0;

    virtual void createCourse( const Course& courseInfo, const CResponseContext& responseContext) = 0;
    virtual void createTest( const quint32 lectureId, const Test& test, const CResponseContext& responseContext) = 0;
    virtual void createLecture( const quint32 courseId, const Lecture& lecture, const CResponseContext& responseContext) = 0;

    virtual void finishTest(const TestUserAnswers& userAnswears, const CResponseContext& responseContext) = 0;
    virtual void finishLecture(const quint32 lectureId, const CResponseContext& responseContext) = 0;

    virtual void getTopicList(const CResponseContext& responseContext) = 0;
    virtual void getCourseList( const CourseListWorkingType workType, const CResponseContext& responseContext) = 0;
    virtual void getCourseListByFilter( const CourseListWorkingType workType, const CourseListFilter& filter, const CResponseContext& responseContext) = 0;
    virtual void getTest(const quint32 lectureId, const CResponseContext& responseContext) = 0;
    virtual void getLecture(const quint32 lectureId, const CResponseContext& responseContext) = 0;
    virtual void getLecturePreviewList(const quint32 courseid, const CResponseContext& responseContext) = 0;


     //responses
    virtual void response_error(const ErrorType result, const CResponseContext& responseContext) override final;
    virtual void response_signIn(const ClientInformation& clientInfo , const CResponseContext& responseContext) override final;
    virtual void response_signUp(const bool result, const CResponseContext& responseContext) override final;
    virtual void response_subscribeOnCourse(const bool result, const CResponseContext& responseContext) override final;

    virtual void response_createTest(const bool result, const CResponseContext& responseContext) override final;
    virtual void response_createLecture(const bool result, const CResponseContext& responseContext) override final;
    virtual void response_createCourse( const quint32 courseid, const CResponseContext& responseContext) override final;

    virtual void response_finishLecture(const bool result, const CResponseContext& responseContext) override final;
    virtual void response_finishTest(const qreal evaluation, const CResponseContext& responseContext) override final;

    virtual void response_getTest( const Test& test, const CResponseContext& responseContext ) override final;
    virtual void response_getLecture( const Lecture& lecture, const CResponseContext& responseContext ) override final;
    virtual void response_getLecturePreviewList( const QVector<Lecture>& lectureList, const CResponseContext& responseContext ) override final;
    virtual void response_getTopicList( const QVector<CourseTopic>& topicList, const CResponseContext& responseContext) override final;
    virtual void response_getCourseList( const QVector<Course>& courseList, const CResponseContext& responseContext) override final;

private:

    void sendToClient(QTcpSocket* pSocket, const quint32 requestid, const quint32 seqId);

public slots:
    void slotRemoveConnection();
    void slotNewConnection();
    void slotReadClient();

private:
    QTcpServer* m_ptcpServer;
    quint16     m_nNextBlockSize;
    std::map<quint32, ::std::shared_ptr<CNetworkClient>> mClientList;


};



#endif // CCOURSEPROCESSOR_H
