#ifndef CLIENT_INFORMATION_HPP
#define CLIENT_INFORMATION_HPP

#include <QString>
#include "ClientType.hpp"

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

#endif //CLIENT_INFORMATION_HPP
