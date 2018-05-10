#ifndef SQLSTATEMENT_H
#define SQLSTATEMENT_H

#include "SqlQuery.h"

class SqlTextStorageStatement : public SqlQuery<void>
{
public:
    SqlTextStorageStatement(EStorage storageType);

private:
    virtual void prepareResultOnError() override final;
    virtual void prepareResultOnSuccess() override final;
    virtual QStringList preapareStatement() override final;
};

#endif // SQLSTATEMENT_H
