#include"CourseTypes.h"
#include <QDataStream>

QDataStream& operator <<(QDataStream& stream, const ClientType& type)
{
    quint8 toInt = static_cast<quint8>(type);
    stream << toInt ;
    return stream;
}

QDataStream& operator >>(QDataStream& stream, ClientType& type)
{
    quint8 toInt;
    stream >> toInt ;
     type = static_cast<ClientType>(toInt);
    return stream;
}

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


QDataStream& operator <<(QDataStream& stream, const ClientInformation& clientInfo)
{
    stream << clientInfo.name
           << clientInfo.last_name
           << clientInfo.email
           << clientInfo.phone_number
           << clientInfo.address
           << clientInfo.type;
    return stream;
}

QDataStream& operator >>(QDataStream& stream, ClientInformation& clientInfo)
{
    stream >> clientInfo.name
            >> clientInfo.last_name
            >> clientInfo.email
            >> clientInfo.phone_number
            >> clientInfo.address
            >> clientInfo.type;

    return stream;
}
