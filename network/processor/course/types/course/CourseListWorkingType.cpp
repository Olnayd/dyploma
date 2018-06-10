#include "CourseListWorkingType.hpp"

QDataStream& operator <<(QDataStream& stream, const CourseListWorkingType& type)
{
    quint32 toInt = static_cast<quint32>(type);
    stream << toInt ;
    return stream;
}

QDataStream& operator >>(QDataStream& stream, CourseListWorkingType& type)
{
    quint32 toInt;
    stream >> toInt ;
    type = static_cast<CourseListWorkingType>(toInt);
    return stream;
}
