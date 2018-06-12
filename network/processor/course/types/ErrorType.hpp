#ifndef ERRORTYPE_HPP
#define ERRORTYPE_HPP

#include <QDataStream>

//will be extended in future
enum ErrorType
{
    Error_WTF = 0,
    Error_User_Does_Not_Has_Permissions,
    Error_User_Is_Not_Listener_Of_the_Course,
    Error_User_Is_Not_Creator_Of_the_Course,
    Error_Internal_Sql_Error
};

QDataStream& operator >>(QDataStream& stream, ErrorType& type);
QDataStream& operator <<(QDataStream& stream, ErrorType& type);

#endif // ERRORTYPE_HPP
