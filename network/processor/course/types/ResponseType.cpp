#include "ResponseType.hpp"

QDataStream& operator<<(QDataStream& stream, const ResponseType& type)
{
    quint32 toInt = static_cast<quint32>(type);
    stream << toInt ;
    return stream;
}

QDataStream& operator>>(QDataStream& stream, ResponseType& type)
{
    quint32 toRequestType;
    stream >> toRequestType ;
    type = static_cast<ResponseType>(toRequestType);
    return stream;
}
