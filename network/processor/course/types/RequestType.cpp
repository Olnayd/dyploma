#include "RequestType.hpp"

QDataStream& operator<<(QDataStream& stream, const RequestType& type)
{
    quint32 toInt = static_cast<quint32>(type);
    stream << toInt ;
    return stream;
}

QDataStream& operator>>(QDataStream& stream, RequestType& type)
{
    quint32 toRequestType;
    stream >> toRequestType ;
    type = static_cast<RequestType>(toRequestType);
    return stream;
}
