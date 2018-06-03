#ifndef COURSEINFORMATION_H
#define COURSEINFORMATION_H

#include "CourseTopic.hpp"

#include <QVector>
#include <QDataStream>

class CourseInformation
{
public:
    CourseInformation() = default;
    CourseInformation(quint32 id, QString name, QString description);
public:
    quint32 id;
    QString name;
    QVector<CourseTopic> topicList;
    QString description;

    qreal rating; //not working yet;
};


QDataStream& operator >>(QDataStream& stream, CourseInformation& type);
QDataStream& operator <<(QDataStream& stream, const CourseInformation& type);


#endif // COURSEINFORMATION_H
