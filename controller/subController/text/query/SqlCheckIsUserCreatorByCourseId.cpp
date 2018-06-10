#include "SqlCheckIsUserCreatorByCourseId.hpp"

SqlCheckIsUserCreatorByCourseId::SqlCheckIsUserCreatorByCourseId(const qint32 clientDatabaseId, const quint32 courseId)
    : SqlQuery<bool>(TEXT_STORAGE)
    , mClientDatabaseId(clientDatabaseId)
    , mCourseId(courseId)
{

}

QStringList SqlCheckIsUserCreatorByCourseId::preapareStatement()
{
    QStringList result;
    result.push_back( QString( "SELECT id_course, id_user FROM CourseToCreator "
                               "WHERE id_course=%1 AND id_user=%2; ").arg(mCourseId)
                                                                     .arg(mClientDatabaseId));

    return result;
}

bool SqlCheckIsUserCreatorByCourseId::prepareResultOnError()
{
     return false;
}

bool SqlCheckIsUserCreatorByCourseId::prepareResultOnSuccess()
{
    return next();
}
