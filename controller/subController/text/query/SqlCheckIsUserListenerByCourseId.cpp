#include "SqlCheckIsUserListenerByCourseId.hpp"


SqlCheckIsUserListenerByCourseId::SqlCheckIsUserListenerByCourseId(const qint32 clientDatabaseId, const quint32 courseId)
    : SqlQuery<bool>(TEXT_STORAGE)
    , mClientDatabaseId(clientDatabaseId)
    , mCourseId(courseId)
{

}

QStringList SqlCheckIsUserListenerByCourseId::preapareStatement()
{
    QStringList result;
    result.push_back( QString( "SELECT id_course, id_user FROM CourseToListener "
                               "WHERE id_course=%1 AND id_user=%2; ").arg(mCourseId)
                                                                     .arg(mClientDatabaseId));

    return result;
}

bool SqlCheckIsUserListenerByCourseId::prepareResultOnError()
{
     return false;
}

bool SqlCheckIsUserListenerByCourseId::prepareResultOnSuccess()
{
    return next();
}
