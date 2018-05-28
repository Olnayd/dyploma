#ifndef SQLADDNEWUSER_H
#define SQLADDNEWUSER_H

#include "database/query/SqlQuery.h"
#include "network/processor/course/CourseTypes.h"

class SqlSignUp : public SqlQuery<bool>
{
public:
    SqlSignUp(const ClientIdentificator& clientIdent, const ClientInformation& clientInfo );

private:
    virtual bool prepareResultOnError() override final;
    virtual bool prepareResultOnSuccess() override final;
    virtual QStringList preapareStatement() override final;

private:
    ClientIdentificator mClientIdent;
    ClientInformation mClientInfo;

};

#endif // SQLADDNEWUSER_H
