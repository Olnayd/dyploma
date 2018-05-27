#include "CNetworkClient.hpp"

CNetworkClient::CNetworkClient(QTcpSocket* socket, const quint32 clientid)
    : mClientId(clientid)
    , mSocket (socket)
{
    connect(mSocket, SIGNAL(disconnected()),
            this,      SLOT(slot_disconnected()));

    connect(mSocket, SIGNAL(readyRead()),
            this,      SLOT(slot_readyRead()));

    connect(mSocket, SIGNAL(connected()),
            this,      SLOT(slot_connected()));
}

QTcpSocket* CNetworkClient::getSocket()
{
    return mSocket;
}

quint32 CNetworkClient::getClientId()
{
    return mClientId;
}

CNetworkClient::~CNetworkClient()
{
    //delete mSocket;
    mSocket = nullptr;
}

void CNetworkClient::slot_disconnected()
{
    emit disconnected();
}

void CNetworkClient::slot_readyRead()
{
    emit readyRead();
}

void CNetworkClient::slot_connected()
{
    emit connected();
}
