#include "SqlCheckIsUserListener.hpp"


SqlCheckIsUserListener::SqlCheckIsUserListener(const qint32 clientDatabaseId, const quint32 courseId)
    : SqlQuery<bool>(TEXT_STORAGE)
    , mClientDatabaseId(clientDatabaseId)
    , mCourseId(courseId)
{

}

QStringList SqlCheckIsUserListener::preapareStatement()
{
    QStringList result;
    result.push_back( QString( "SELECT id_course, id_user FROM CourseToListener "
                               "WHERE id_course=%1 AND id_user=%2; ").arg(mCourseId)
                                                                     .arg(mClientDatabaseId));

    return result;
}

bool SqlCheckIsUserListener::prepareResultOnError()
{
     return false;
}

bool SqlCheckIsUserListener::prepareResultOnSuccess()
{
    return next();
}
