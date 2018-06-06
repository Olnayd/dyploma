#include "SqlCheckIsUserCreator.hpp"

SqlCheckIsUserCreator::SqlCheckIsUserCreator(const qint32 clientDatabaseId, const quint32 courseId)
    : SqlQuery<bool>(TEXT_STORAGE)
    , mClientDatabaseId(clientDatabaseId)
    , mCourseId(courseId)
{

}

QStringList SqlCheckIsUserCreator::preapareStatement()
{
    QStringList result;
    result.push_back( QString( "SELECT id_course, id_user FROM CourseToCreator "
                               "WHERE id_course=%1 AND id_user=%2; ").arg(mCourseId)
                                                                     .arg(mClientDatabaseId));

    return result;
}

bool SqlCheckIsUserCreator::prepareResultOnError()
{
     return false;
}

bool SqlCheckIsUserCreator::prepareResultOnSuccess()
{
    return next();
}
