#ifndef COURSETOPIC_H
#define COURSETOPIC_H

#include <QDataStream>

class CourseTopic
{
public:
    CourseTopic() = default;
    CourseTopic( const quint32 id_, const QString& name_);
    quint32 id;
    QString name;

};

QDataStream& operator >>(QDataStream& stream,CourseTopic& type);
QDataStream& operator <<(QDataStream& stream,const CourseTopic& type);


#endif // COURSETOPIC_H
