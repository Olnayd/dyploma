#include "SqlSubscribeOnCourse.h"

SqlSubscribeOnCourse::SqlSubscribeOnCourse(const quint32 courseId, const quint32 clientdatabaseId)
    : SqlQuery<bool>(TEXT_STORAGE)
    , mCourseId(courseId)
    , mClientDatabaseId(clientdatabaseId)
{

}

QStringList SqlSubscribeOnCourse::preapareStatement()
{
    QStringList result;
    result.push_back( QString( "INSERT INTO CourseToListener(id_user,id_course) "
                               "VALUES (%1,%2); ").arg(mClientDatabaseId)
                                                  .arg(mCourseId));

    return result;
}

bool SqlSubscribeOnCourse::prepareResultOnError()
{
    return false;
}

bool SqlSubscribeOnCourse::prepareResultOnSuccess()
{
    return true;
}
