#include "SqlSignUp.hpp"

SqlSignUp::SqlSignUp(const ClientIdentificator& clientIdent, const ClientInformation& clientInfo )
    : SqlQuery<bool>(TEXT_STORAGE)
    , mClientIdent(clientIdent)
    , mClientInfo(clientInfo)
{

}

QStringList SqlSignUp::preapareStatement()
{
    QStringList result;
    result.push_back( QString( "INSERT INTO USER (login, password, name, last_name, phone_number, email, address, type)  \
                                VALUES ('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8');").arg( mClientIdent.login )
                                                                      .arg( mClientIdent.password )
                                                                      .arg( mClientInfo.name )
                                                                      .arg( mClientInfo.last_name )
                                                                      .arg( mClientInfo.phone_number )
                                                                      .arg( mClientInfo.email )
                                                                      .arg( mClientInfo.address )
                                                                      .arg( (int)mClientInfo.type));
    return result;
}

bool SqlSignUp::prepareResultOnError()
{
    return false;
}
bool SqlSignUp::prepareResultOnSuccess()
{
    return true;
}

