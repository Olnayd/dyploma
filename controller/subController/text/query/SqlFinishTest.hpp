#ifndef SQLFINISHTEST_H
#define SQLFINISHTEST_H

#include "SqlCreateLecture.hpp"
#include "database/query/SqlQuery.h"

class SqlFinishTest : public SqlQuery<bool>
{
public:
    SqlFinishTest(const quint32 testId, const quint32 userDatabaseId, const qreal evaluation);

private:
    virtual bool prepareResultOnError() override final;
    virtual bool prepareResultOnSuccess() override final;
    virtual QStringList preapareStatement() override final;

private:
    quint32 mTestId;
    quint32 mClientDatabaseId;
    qreal mEvaluation;
};


#endif // SQLFINISHTEST_H
