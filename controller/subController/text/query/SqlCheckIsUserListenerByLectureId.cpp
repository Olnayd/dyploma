#include "SqlCheckIsUserListenerByLectureId.hpp"

SqlCheckIsUserListenerByLectureId::SqlCheckIsUserListenerByLectureId(const qint32 clientDatabaseId, const quint32 lectureId)
    : SqlQuery<bool>(TEXT_STORAGE)
    , mClientDatabaseId(clientDatabaseId)
    , mLectureId(lectureId)
{

}

QStringList SqlCheckIsUserListenerByLectureId::preapareStatement()
{
    QStringList result;
    result.push_back( QString( " SELECT * FROM CourseToListener "
                               " Inner join CourseToLecture on CourseToLecture.id_course = CourseToListener.id_course "
                               " where CourseToLecture.id_lecture = %1 and CourseToListener.id_user = %2 ").arg(mLectureId)
                                                                                                          .arg(mClientDatabaseId));

    return result;
}

bool SqlCheckIsUserListenerByLectureId::prepareResultOnError()
{
     return false;
}

bool SqlCheckIsUserListenerByLectureId::prepareResultOnSuccess()
{
    return next();
}
