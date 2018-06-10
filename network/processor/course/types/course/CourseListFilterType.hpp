#ifndef COURSELISTFILTERTYPE_H
#define COURSELISTFILTERTYPE_H

#include <QDataStream>

enum CourseListFilterType
{
    BY_RATING_HIGHER_FISRT,
    BY_RATING_SMALLEST_FIRST,
    BY_TOPIC,
    BY_NEWEST, // not working yet
    BY_LASTEST //not working yet
};

QDataStream& operator >>(QDataStream& stream, CourseListFilterType& type);
QDataStream& operator <<(QDataStream& stream, CourseListFilterType& type);

#endif // COURSELISTFILTERTYPE_H
