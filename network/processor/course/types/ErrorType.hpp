#ifndef ERRORTYPE_HPP
#define ERRORTYPE_HPP

#include <QDataStream>

//will be extended in future
enum ErrorType
{
    Error_WTF = 0
};

QDataStream& operator >>(QDataStream& stream, ErrorType& type);
QDataStream& operator <<(QDataStream& stream, ErrorType& type);

#endif // ERRORTYPE_HPP
