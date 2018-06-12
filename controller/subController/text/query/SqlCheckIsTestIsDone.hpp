#ifndef SQLCHECKISTESTISDONE_H
#define SQLCHECKISTESTISDONE_H

#include "database/query/SqlQuery.h"

class SqlCheckIsTestIsDone : public SqlQuery<bool>
{
public:
    SqlCheckIsTestIsDone(const qint32 clientDatabaseId, const quint32 testId);

private:
    virtual bool prepareResultOnError() override final;
    virtual bool prepareResultOnSuccess() override final;
    virtual QStringList preapareStatement() override final;
public:
    qreal evaluation;

private:
    qint32 mClientDatabaseId;
    quint32 mTestId;
};
#endif // SQLCHECKISTESTISDONE_H
