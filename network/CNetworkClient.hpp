#ifndef CCLIENT_H
#define CCLIENT_H

#include <QObject>
#include<QTcpSocket>

class CNetworkClient : public QObject
{
    Q_OBJECT
public:
    CNetworkClient(QTcpSocket* mSocket, const quint32 clientID);
    ~CNetworkClient();

    QTcpSocket* getSocket();
    quint32 getClientId();
signals:
    void connected();
    void disconnected();
    void readyRead();

private slots:
    void slot_connected();
    void slot_disconnected();
    void slot_readyRead();

private:
    quint32 mClientId;
    QTcpSocket* mSocket;
};

#endif // CCLIENT_H
