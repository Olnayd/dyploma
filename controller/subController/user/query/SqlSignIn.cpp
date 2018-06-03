#include "SqlSignIn.hpp"


SqlSignIn::SqlSignIn(const ClientIdentificator& clientIdent)
    : SqlQuery<ClientInformation>(TEXT_STORAGE)
    , mClientDatabaseId(-1)
    , mClientIdent(clientIdent)

{

}

QStringList SqlSignIn::preapareStatement()
{
    QStringList result;
    result.push_back( QString( " SELECT name, last_name, phone_number, email, address, type, id FROM User"
                               " WHERE login ='%1' AND password ='%2';" ).arg(mClientIdent.login)
                                                                        .arg(mClientIdent.password));
    return result;
}

ClientInformation SqlSignIn::prepareResultOnError()
{
    return ClientInformation();
}
ClientInformation SqlSignIn::prepareResultOnSuccess()
{
    ClientInformation result;
    if(next())
    {
        result.name         = value(0).toString();
        result.last_name    = value(1).toString();
        result.phone_number = value(2).toString();
        result.email        = value(3).toString();
        result.address      = value(4).toString();
        result.type         = static_cast<ClientType>(value(5).toInt());
        mClientDatabaseId   = value(6).toInt();
    }

    return result;
}

qint32 SqlSignIn::getClientDatabaseId()
{
    return mClientDatabaseId;
}

