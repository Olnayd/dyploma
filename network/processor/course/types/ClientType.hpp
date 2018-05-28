
#ifndef CLIENT_TYPE_HPP
#define CLIENT_TYPE_HPP

#include <QDataStream>

enum ClientType
{
    Student = 0,
    Teacher,
    Unknown = 999
};

QDataStream& operator >>(QDataStream& stream, ClientType& type);
QDataStream& operator <<(QDataStream& stream, ClientType& type);

#endif //CLIENT_TYPE_HPP
