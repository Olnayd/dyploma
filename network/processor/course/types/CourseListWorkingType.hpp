#ifndef COURSELISTWORKINGTYPE_H
#define COURSELISTWORKINGTYPE_H

#include <QDataStream>

enum CourseListWorkingType
{
    ALL,
    USER_IS_LISTENER,
    USER_IS_CREATOR
};


QDataStream& operator >>(QDataStream& stream, CourseListWorkingType& type);
QDataStream& operator <<(QDataStream& stream, CourseListWorkingType& type);

#endif // COURSELISTWORKINGTYPE_H
