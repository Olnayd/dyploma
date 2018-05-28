#include "ClientType.hpp"

QDataStream& operator <<(QDataStream& stream, const ClientType& type)
{
    quint32 toInt = static_cast<quint32>(type);
    stream << toInt ;
    return stream;
}

QDataStream& operator >>(QDataStream& stream, ClientType& type)
{
    quint32 toInt;
    stream >> toInt ;
     type = static_cast<ClientType>(toInt);
    return stream;
}
