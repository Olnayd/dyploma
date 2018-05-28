#ifndef SQLAUTORIZEUSER_H
#define SQLAUTORIZEUSER_H

#include "network/processor/course/types/ClientInformation.hpp"
#include "network/processor/course/types/ClientIdentificator.hpp"
#include "database/query/SqlQuery.h"

class SqlSignIn : public SqlQuery<ClientInformation>
{
public:
    SqlSignIn(const ClientIdentificator& clientIdent);

private:
    virtual ClientInformation prepareResultOnError() override final;
    virtual ClientInformation prepareResultOnSuccess() override final;
    virtual QStringList preapareStatement() override final;
private:
    ClientIdentificator mClientIdent;
};


#endif // SQLAUTORIZEUSER_H
