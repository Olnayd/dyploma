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
#include "query/SqlCreateLection.hpp"
#include "query/SqlCheckIsUserCreator.hpp"
#include "query/SqlCheckIsUserListener.hpp"



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

void CTextStorageSubCtrl::createLection(const qint32 clientdatabaseid, const quint32 courseid, const LectionInformation& lectionInfo, const CResponseContext& responseContext, ICourseResponseHandle& reponseHandle)
{
    SqlCheckIsUserCreator query(clientdatabaseid, courseid);
    if(mSqlController->executeQuery(query) && query.getResult())
    {
        SqlCreateLection queryCreateLection(lectionInfo, courseid);
        if(mSqlController->executeQuery(queryCreateLection))
        {
            reponseHandle.response_createLection(queryCreateLection.getResult(),responseContext);
        }
        else
            reponseHandle.response_error(Error_WTF, responseContext);
    }
    else
        reponseHandle.response_error(Error_WTF, responseContext);
}

void CTextStorageSubCtrl::getLection( const qint32 clientdatabaseid, const quint32 lectionId, const CResponseContext& responseContext, ICourseResponseHandle& reponseHandle)
{

}

void CTextStorageSubCtrl::getLectionPreviewList(const quint32 courseid, const CResponseContext& responseContext, ICourseResponseHandle& reponseHandle)
{

}
