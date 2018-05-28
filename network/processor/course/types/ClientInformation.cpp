#include "ClientInformation.hpp"

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
