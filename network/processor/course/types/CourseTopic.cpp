#include "CourseTopic.hpp"

CourseTopic::CourseTopic( const quint32 id_, const QString& name_)
 : id(id_), name(name_)
{

}


QDataStream& operator >>(QDataStream& stream, CourseTopic& type)
{
    stream >> type.id >> type.name ;
 }

QDataStream& operator <<(QDataStream& stream, const CourseTopic& type)
{
    stream << type.id << type.name;
}
