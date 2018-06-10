#ifndef COURSEINFORMATION_H
#define COURSEINFORMATION_H

#include "CourseTopic.hpp"

#include <QVector>
#include <QDataStream>

class Course
{
public:
    Course() = default;
    Course(quint32 id, QString name, QString description);
public:
    quint32 id;

    QString name;
    QVector<CourseTopic> topicList;
    QString description;

    qreal rating; //not working yet;
};


QDataStream& operator >>(QDataStream& stream, Course& type);
QDataStream& operator <<(QDataStream& stream, const Course& type);


#endif // COURSEINFORMATION_H
