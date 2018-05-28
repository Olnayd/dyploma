#include "ErrorType.hpp"

QDataStream& operator <<(QDataStream& stream, const ErrorType& type)
{
    quint32 toInt = static_cast<quint32>(type);
    stream << toInt ;
    return stream;
}

QDataStream& operator >>(QDataStream& stream, ErrorType& type)
{
    quint32 toInt;
    stream >> toInt ;
    type = static_cast<ErrorType>(toInt);
    return stream;
}
