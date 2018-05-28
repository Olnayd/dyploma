#ifndef CLIENT_IDENTIFICATOR_HPP
#define CLIENT_IDENTIFICATOR_HPP

#include <QString>

class ClientIdentificator
{
public:
    friend QDataStream& operator <<(QDataStream& stream, const ClientIdentificator& clientIdent);
    friend QDataStream& operator >>(QDataStream& stream, ClientIdentificator& clientIdent);

public:
    QString login;
    QString password;
};

#endif //CLIENT_IDENTIFICATOR_HPP

