#include "SqlFinishLecture.hpp"

SqlFinishLecture::SqlFinishLecture(const quint32 testId, const quint32 clientdatabaseId )
    : SqlQuery<bool>(TEXT_STORAGE)
    , mTestId(testId)
    , mClientDatabaseId(clientdatabaseId)
{

}

QStringList SqlFinishLecture::preapareStatement()
{
    QStringList result;
    result.push_back( QString( "INSERT INTO LectureToUser(id_user,id_lecture) "
                               "VALUES (%1,%2); ").arg(mClientDatabaseId)
                                                     .arg(mTestId));

    return result;
}

bool SqlFinishLecture::prepareResultOnError()
{
    return false;
}

bool SqlFinishLecture::prepareResultOnSuccess()
{
    return true;
}
