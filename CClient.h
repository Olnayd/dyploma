#ifndef CCLIENT_H
#define CCLIENT_H


#include<QTcpSocket>

class CClient
{
public:
    CClient(QTcpSocket* mSocket);

    QTcpSocket* getSocket();
signals:
    void connected();
    void disconnected();
    void readyRead();

private slots:
    void slot_connected();
    void slot_disconnected();
    void slot_readyRead();

private:
    QTcpSocket* mSocket;
};

#endif // CCLIENT_H
