#include "SqlFinishTest.hpp"

SqlFinishTest::SqlFinishTest(const quint32 testId, const quint32 clientdatabaseId, const qreal evaluation)
    : SqlQuery<bool>(TEXT_STORAGE)
    , mTestId(testId)
    , mClientDatabaseId(clientdatabaseId)
    , mEvaluation(evaluation)
{

}

QStringList SqlFinishTest::preapareStatement()
{
    QStringList result;
    result.push_back( QString( "INSERT INTO TestToUser(id_user,id_test,evaluation) "
                               "VALUES (%1,%2,%3); ").arg(mClientDatabaseId)
                                                     .arg(mTestId)
                                                     .arg(mEvaluation));

    return result;
}

bool SqlFinishTest::prepareResultOnError()
{
    return false;
}

bool SqlFinishTest::prepareResultOnSuccess()
{
    return true;
}
