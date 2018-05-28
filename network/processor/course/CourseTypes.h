#ifndef COURSETYPES_H
#define COURSETYPES_H

#include <QString>

enum ClientType
{
    Strudent = 0,
    Teacher
};

class ClientInformation
{
public:
    friend QDataStream& operator <<(QDataStream& stream, const ClientInformation& clientInfo);
    friend QDataStream& operator >>(QDataStream& stream, ClientInformation& clientInfo);

public:
    QString name;
    QString last_name;
    QString email;
    ClientType type;
    //Optional
    QString phone_number;
    QString address;


};

class ClientIdentificator
{
public:
    friend QDataStream& operator <<(QDataStream& stream, const ClientIdentificator& clientIdent);
    friend QDataStream& operator >>(QDataStream& stream, ClientIdentificator& clientIdent);

public:
    QString login;
    QString password;
};








#endif // COURSETYPES_H
