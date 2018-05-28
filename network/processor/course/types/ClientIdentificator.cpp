
#include "ClientIdentificator.hpp"

QDataStream& operator <<(QDataStream& stream, const ClientIdentificator& clientIdent)
{
    stream << clientIdent.login
           << clientIdent.password;
    return stream;
}

QDataStream& operator >>(QDataStream& stream, ClientIdentificator& clientIdent)
{
    stream >> clientIdent.login
           >> clientIdent.password;
    return stream;
}
