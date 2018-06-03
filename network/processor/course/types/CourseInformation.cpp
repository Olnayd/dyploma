#include "CourseInformation.hpp"
#include <QDataStream>

CourseInformation::CourseInformation(quint32 id_, QString name_, QString description_)
    : id(id_)
    , name(name_)
    , topicList()
    , description(description_)
    , rating(-1)
{

}

QDataStream& operator >>(QDataStream& stream, CourseInformation& type)
{
    stream >> type.id >> type.name >> type.description >> type.topicList >> type.rating;
    return stream;
}

QDataStream& operator <<(QDataStream& stream, const CourseInformation& type)
{
    stream << type.id << type.name << type.description << type.topicList << type.rating;
    return stream;
}
