#include "SqlCheckIsUserCreatorByLectureId.hpp"


SqlCheckIsUserCreatorByLectureId::SqlCheckIsUserCreatorByLectureId(const qint32 clientDatabaseId, const quint32 lectureId)
    : SqlQuery<bool>(TEXT_STORAGE)
    , mClientDatabaseId(clientDatabaseId)
    , mLectureId(lectureId)
{

}

QStringList SqlCheckIsUserCreatorByLectureId::preapareStatement()
{
    QStringList result;
    result.push_back( QString( " SELECT * FROM CourseToCreator "
                               " Inner join CourseToLecture on CourseToLecture.id_course = CourseToCreator.id_course "
                               " where CourseToLecture.id_lecture = %1 and CourseToCreator.id_user = %2 ").arg(mLectureId)
                                                                                                          .arg(mClientDatabaseId));

    return result;
}

bool SqlCheckIsUserCreatorByLectureId::prepareResultOnError()
{
     return false;
}

bool SqlCheckIsUserCreatorByLectureId::prepareResultOnSuccess()
{
    return next();
}
