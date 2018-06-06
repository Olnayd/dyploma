#ifndef LECTIONINFORMATION_H
#define LECTIONINFORMATION_H

#include <QDataStream>

class LectionInformation
{
public:
    LectionInformation() = default;
    LectionInformation(QString name_, QString description_, QString data_);

    QString name;
    QString description;
    QString data;

};

QDataStream& operator >>(QDataStream& stream, LectionInformation& type);
QDataStream& operator <<(QDataStream& stream, const LectionInformation& type);


#endif // LECTIONINFORMATION_H
