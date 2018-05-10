#ifndef SQLIMAGESTORAGESTATEMENT_H
#define SQLIMAGESTORAGESTATEMENT_H

#include "SqlQuery.h"

class SqlImageStorageStatement : public SqlQuery<void>
{
public:
    SqlImageStorageStatement(EStorage storageType);

private:
    virtual void prepareResultOnError() override final;
    virtual void prepareResultOnSuccess() override final;
    virtual QStringList preapareStatement() override final;

};

#endif // SQLIMAGESTORAGESTATEMENT_H
