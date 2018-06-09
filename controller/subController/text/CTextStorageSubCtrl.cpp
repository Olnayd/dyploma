#include "CTextStorageSubCtrl.h"

#include <QDebug>
#include "database/CSqlConstants.h"
#include "database/query/SqlGetSchemaVersion.h"
#include "query/SqlTextStorageStatement.hpp"
#include "query/SqlGetTopicList.hpp"
#include "query/SqlGetAllCourses.hpp"
#include "query/SqlGetTopicListForCourse.hpp"
#include "query/SqlGetCourseListWhereUserIsCreator.hpp"
#include "query/SqlGetCourseListWhereUserIsListener.hpp"
#include "query/SqlSubscribeOnCourse.h"
#include "query/SqlCreateCourse.hpp"
#include "query/SqlCreateLecture.hpp"
#include "query/SqlCheckIsUserCreator.hpp"
#include "query/SqlCheckIsUserListener.hpp"
#include "query/SqlCoupleLectureToCourse.hpp"
#include "query/SqlCreateTest.hpp"
#include "query/SqlGetLecture.hpp"
#include "query/SqlGetLecturePreviewList.hpp"
#include "query/SqlCheckIsLectureIsDone.hpp"



CTextStorageSubCtrl::CTextStorageSubCtrl(std::shared_ptr<CSqlSubCtrl> sqlController)
     : mSqlController( sqlController )
{

}

bool CTextStorageSubCtrl::init()
{
    SqlGetSchemaVersion stmt (EStorage::TEXT_STORAGE) ;
    mSqlController->executeQuery(stmt);
    common::version dbVersion = stmt.getResult();

    if ( database::constant::TextStorageVersion != dbVersion)
    {
        qDebug()<< "[" << getName() << "]"
                << "different database versions. Expected"
                << database::constant::TextStorageVersion.major
                << ":"
                << database::constant::TextStorageVersion.minor
                << "but"
                << dbVersion.major
                << ":"
                << dbVersion.minor
                << "is come.";

        SqlTextStorageStatement stmtInitImage (EStorage::TEXT_STORAGE);
        if ( !mSqlController->executeQuery(stmtInitImage) )
        {
            qDebug()<< "[" << getName() << "]" << "re-creation of DB failed";
            return false;
        }
    }
    return true;
}

const char* CTextStorageSubCtrl::getName()
{
    return "CTextStorageSubCtrl";
}

bool CTextStorageSubCtrl::prepareShutdown()
{
    return true;
}


void CTextStorageSubCtrl::getTopicList(const CResponseContext& responseContext, ICourseResponseHandle& reponseHandle)
{
    SqlGetTopicList query;
    if(mSqlController->executeQuery(query))
    {
        reponseHandle.response_getTopicList(query.getResult(), responseContext);
    }
    else
        reponseHandle.response_error(Error_WTF, responseContext);
}

void CTextStorageSubCtrl::getCourseListByFilter( const qint32 clientdatabaseid, const CourseListWorkingType workType, const CourseListFilter& filter, const CResponseContext& responseContext, ICourseResponseHandle& reponseHandle)
{
    SqlQuery<QVector<Course>>* queryFetchAllCourses;
    switch(workType)
    {
    case CourseListWorkingType::ALL: queryFetchAllCourses = new SqlGetAllCourses(filter);break;
    case CourseListWorkingType::USER_IS_CREATOR: queryFetchAllCourses = new SqlGetCourseListWhereUserIsCreator(filter, clientdatabaseid); break;
    case CourseListWorkingType::USER_IS_LISTENER: queryFetchAllCourses = new SqlGetCourseListWhereUserIsListener(filter, clientdatabaseid); break;
    }

    if(mSqlController->executeQuery(*queryFetchAllCourses))
    {
        QVector<Course> courseInfoList = queryFetchAllCourses->getResult();
        for(Course& course : courseInfoList)
        {
            SqlGetTopicListForCourse queryTopicListForCourse(course.id);
            if(mSqlController->executeQuery(queryTopicListForCourse))
            {
                course.topicList = queryTopicListForCourse.getResult();
            }
        }
        reponseHandle.response_getCourseList(courseInfoList, responseContext);
    }
    else
        reponseHandle.response_error(Error_WTF, responseContext);
}

void CTextStorageSubCtrl::subscribeOnCourse( const qint32 clientdatabaseid,const quint32 courseid, const CResponseContext& responseContext, ICourseResponseHandle& reponseHandle)
{
    SqlSubscribeOnCourse query(courseid, clientdatabaseid);
    if(mSqlController->executeQuery(query))
    {
        reponseHandle.response_subscribeOnCourse(query.getResult(), responseContext);
    }
    else
        reponseHandle.response_error(Error_WTF, responseContext);
}

void CTextStorageSubCtrl::createCourse( const qint32 clientdatabaseid, const Course& courseInfo, const CResponseContext& responseContext, ICourseResponseHandle& reponseHandle)
{
    SqlCreateCourse query(courseInfo, clientdatabaseid);
    if(mSqlController->executeQuery(query))
    {
        reponseHandle.response_createCourse(query.getResult(), responseContext);
    }
    else
        reponseHandle.response_error(Error_WTF, responseContext);

}

void CTextStorageSubCtrl::createLecture(const qint32 clientDatabaseId, const quint32 courseId, const Lecture& lecture, const CResponseContext& responseContext, ICourseResponseHandle& reponseHandle)
{
    SqlCheckIsUserCreator queryIsUserCreator(clientDatabaseId, courseId);
    if(mSqlController->executeQuery(queryIsUserCreator) && queryIsUserCreator.getResult())
    {
        std::shared_ptr<SqlCreateLecture>         queryCreateLecture         = ::std::make_shared<SqlCreateLecture>(lecture);
        std::shared_ptr<SqlCoupleLectureToCourse> queryCoupleLectureToCourse = ::std::make_shared<SqlCoupleLectureToCourse>(courseId, queryCreateLecture);
        std::shared_ptr<SqlCreateTest>            queryCreateTest;

        QVector<std::shared_ptr<SqlQuery<quint32>>> toExecute;
        toExecute.push_back(queryCreateLecture);
        toExecute.push_back(queryCoupleLectureToCourse);

        if(lecture.__isset.test)
        {
            queryCreateTest = ::std::make_shared<SqlCreateTest>(lecture.Test(), queryCreateLecture);
            toExecute.push_back(queryCreateTest);
        }

        if(mSqlController->executeQueryList(toExecute))
        {
            if(queryCreateLecture->getResult() && queryCoupleLectureToCourse->getResult() && queryCreateTest->getResult())
                reponseHandle.response_createLecture(true,responseContext);
            else
                reponseHandle.response_createLecture(false,responseContext);
        }
        else
            reponseHandle.response_error(Error_WTF, responseContext);
    }
    else
        reponseHandle.response_error(Error_WTF, responseContext);
}

void CTextStorageSubCtrl::getLecture( const qint32 clientDatabaseId, const quint32 lectureId, const CResponseContext& responseContext, ICourseResponseHandle& reponseHandle)
{
    SqlGetLecture queryGetLecture(lectureId);
    if(mSqlController->executeQuery(queryGetLecture))
    {
        SqlCheckIsLectureIsDone queryCheckIsLectureDone(clientDatabaseId, lectureId);
        if(mSqlController->executeQuery(queryCheckIsLectureDone))
        {
            Lecture result = queryGetLecture.getResult();
            result.setIsLectureDone(queryCheckIsLectureDone.getResult());
            reponseHandle.response_getLecture(result, responseContext);
        }

    }
    else
        reponseHandle.response_error(Error_WTF, responseContext);
}

void CTextStorageSubCtrl::getLecturePreviewList( const qint32 clientDatabaseId, const quint32 courseid, const CResponseContext& responseContext, ICourseResponseHandle& reponseHandle)
{
    SqlGetLecturePreviewList queryGetLecturePreviewList(courseid);
    if(mSqlController->executeQuery(queryGetLecturePreviewList))
    {
       bool isErrorOccurs;
        QVector<Lecture> result = queryGetLecturePreviewList.getResult();

        for (Lecture& lecture : result)
        {
            SqlCheckIsLectureIsDone queryCheckIsLectureDone(clientDatabaseId, lecture.IdByRef());
            if(!mSqlController->executeQuery(queryCheckIsLectureDone))
            {isErrorOccurs =true; break;}
            lecture.setIsLectureDone(queryCheckIsLectureDone.getResult());
        }

        if(isErrorOccurs)
            reponseHandle.response_error(Error_WTF, responseContext);
        else
            reponseHandle.response_getLecturePreviewList(result, responseContext);
    }
    else
        reponseHandle.response_error(Error_WTF, responseContext);
}
