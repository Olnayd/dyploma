#ifndef SQLGETSCHEMAVERSION_H
#define SQLGETSCHEMAVERSION_H

#include "SqlQuery.h"
#include "common/version.h"

class SqlGetSchemaVersion : public SqlQuery<common::version>
{
public:
    SqlGetSchemaVersion(EStorage storageType);
private:
    virtual common::version prepareResultOnError() override final;
    virtual common::version prepareResultOnSuccess() override final;
    virtual QStringList preapareStatement() override final;

};
#endif // SQLGETSCHEMAVERSION_H
