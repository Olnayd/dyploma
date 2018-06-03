#ifndef SQLTEXTSTORAGESTATEMENT_H
#define SQLTEXTSTORAGESTATEMENT_H

#include "database/query/SqlQuery.h"

class SqlTextStorageStatement : public SqlQuery<void>
{
public:
    SqlTextStorageStatement(EStorage storageType);

private:
    virtual void prepareResultOnError() override final;
    virtual void prepareResultOnSuccess() override final;
    virtual QStringList preapareStatement() override final;
};

#endif // SQLTEXTSTORAGESTATEMENT_H
