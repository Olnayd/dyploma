#include "CClient.h"

CClient::CClient(QTcpSocket* socket)
    :mSocket (socket)
{
    connect(mSocket, SIGNAL(disconnected()),
            this,      SLOT(slot_disconnected()));

    connect(mSocket, SIGNAL(readyRead()),
            this,      SLOT(slot_readyRead()));

    connect(mSocket, SIGNAL(connected()),
            this,      SLOT(slot_connected());
}

void CClient::slot_disconnected()
{
    emit disconnected();
}

void CClient::slot_readyRead()
{
    emit readyRead();
}

void CClient::slot_connected()
{
    emit connected();
}
