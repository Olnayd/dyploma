#include "Course.hpp"
#include <QDataStream>

Course::Course(quint32 id_, QString name_, QString description_)
    : id(id_)
    , name(name_)
    , topicList()
    , description(description_)
    , rating(-1)
{

}

QDataStream& operator >>(QDataStream& stream, Course& type)
{
    stream >> type.id >> type.name >> type.description >> type.topicList >> type.rating;
    return stream;
}

QDataStream& operator <<(QDataStream& stream, const Course& type)
{
    stream << type.id << type.name << type.description << type.topicList << type.rating;
    return stream;
}
