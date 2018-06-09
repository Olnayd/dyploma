#include "SqlCheckIsLectureIsDone.hpp"

SqlCheckIsLectureIsDone::SqlCheckIsLectureIsDone(const qint32 clientDatabaseId, const quint32 lectureId)
    : SqlQuery<bool>(TEXT_STORAGE)
    , mClientDatabaseId(clientDatabaseId)
    , mLectureId(lectureId)
{

}

QStringList SqlCheckIsLectureIsDone::preapareStatement()
{
    QStringList result;
    result.push_back( QString( " SELECT id_lecture, id_user FROM LectureToUser "
                               " WHERE id_user = %1 AND id_lecture = %2 ").arg(mClientDatabaseId).arg(mLectureId));

    return result;
}

bool SqlCheckIsLectureIsDone::prepareResultOnError()
{
     return false;
}

bool SqlCheckIsLectureIsDone::prepareResultOnSuccess()
{
    return next();
}
