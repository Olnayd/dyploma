#ifndef COURSELISTFILTER_H
#define COURSELISTFILTER_H

#include <QDataStream>
#include "CourseListFilterType.hpp"

class CourseListFilter
{
public:

    CourseListFilter() = default;
    CourseListFilter(const CourseListFilterType filterType_, const quint32 id_ = -1);
    CourseListFilterType filterType;
    quint32 id; //additional id for choosing topic

};

QDataStream& operator >>(QDataStream& stream, CourseListFilter& type);
QDataStream& operator <<(QDataStream& stream, const CourseListFilter& type);


#endif // COURSELISTFILTER_H
