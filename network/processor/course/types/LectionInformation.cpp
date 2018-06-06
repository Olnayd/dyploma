#include "LectionInformation.hpp"

LectionInformation::LectionInformation(QString name_, QString description_, QString data_)
    :name(name_), description(description_), data(data_)
{

}

QDataStream& operator >>(QDataStream& stream, LectionInformation& type)
{
    stream >> type.name >> type.description >> type.data >> type.isTestExist;
    return stream;
}

QDataStream& operator <<(QDataStream& stream, const LectionInformation& type)
{
    stream << type.name << type.description << type.data << type.isTestExist;
    return stream;
}
