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
#include "query/SqlCreateLection.hpp"


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
    SqlQuery<QVector<CourseInformation>>* queryFetchAllCourses;
    switch(workType)
    {
    case CourseListWorkingType::ALL: queryFetchAllCourses = new SqlGetAllCourses(filter);break;
    case CourseListWorkingType::USER_IS_CREATOR: queryFetchAllCourses = new SqlGetCourseListWhereUserIsCreator(filter, clientdatabaseid); break;
    case CourseListWorkingType::USER_IS_LISTENER: queryFetchAllCourses = new SqlGetCourseListWhereUserIsListener(filter, clientdatabaseid); break;
    }

    if(mSqlController->executeQuery(*queryFetchAllCourses))
    {
        QVector<CourseInformation> courseInfoList = queryFetchAllCourses->getResult();
        for(CourseInformation& course : courseInfoList)
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

void CTextStorageSubCtrl::createLection( const qint32 clientdatabaseid, const CourseInformation& courseInfo, const CResponseContext& responseContext, ICourseResponseHandle& reponseHandle)
{
    SqlCreateLection query(courseInfo, clientdatabaseid);
    if(mSqlController->executeQuery(query))
    {
        reponseHandle.response_createLection(query.getResult(), responseContext);
    }
    else
        reponseHandle.response_error(Error_WTF, responseContext);

}
