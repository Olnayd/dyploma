#include "CourseListFilterType.hpp"

QDataStream& operator <<(QDataStream& stream, const CourseListFilterType& type)
{
    quint32 toInt = static_cast<quint32>(type);
    stream << toInt ;
    return stream;
}

QDataStream& operator >>(QDataStream& stream, CourseListFilterType& type)
{
    quint32 toInt;
    stream >> toInt ;
    type = static_cast<CourseListFilterType>(toInt);
    return stream;
}
