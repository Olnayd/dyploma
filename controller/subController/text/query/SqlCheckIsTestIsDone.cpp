#include "SqlCheckIsTestIsDone.hpp"

SqlCheckIsTestIsDone::SqlCheckIsTestIsDone(const qint32 clientDatabaseId, const quint32 lectureId)
    : SqlQuery<bool>(TEXT_STORAGE)
    , mClientDatabaseId(clientDatabaseId)
    , mTestId(lectureId)
{

}

QStringList SqlCheckIsTestIsDone::preapareStatement()
{
    QStringList result;
    result.push_back( QString( " SELECT id_test, id_user, evaluation FROM TestToUser "
                               " WHERE id_user = %1 AND id_test = %2 ").arg(mClientDatabaseId).arg(mTestId));

    return result;
}

bool SqlCheckIsTestIsDone::prepareResultOnError()
{
     return false;
}

bool SqlCheckIsTestIsDone::prepareResultOnSuccess()
{
    while(next())
    {
        evaluation = value(2).toDouble();
        return true;
    }
    return false;

}
