#include "CourseListFilter.hpp"

CourseListFilter::CourseListFilter(const CourseListFilterType filterType_, const quint32 id_)
    : filterType(filterType_)
    , id(id_)
{

}

QDataStream& operator <<(QDataStream& stream, const CourseListFilter& type)
{
    stream << type.filterType << type.id;
    return stream;
}

QDataStream& operator >>(QDataStream& stream, CourseListFilter& type)
{
    stream >> type.filterType >> type.id ;
    return stream;
}
