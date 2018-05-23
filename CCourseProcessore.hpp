#ifndef CCOURSEPROCESSOR_H
#define CCOURSEPROCESSOR_H

#include<tuple>
#include "CClient.h"
#include<QTcpServer>

class CCourseProcessor : public QObject
{
    Q_OBJECT
private:
    QTcpServer* m_ptcpServer;
    quint16     m_nNextBlockSize;

private:
    void sendToClient(QTcpSocket* pSocket, const QString& str);

    template <typename... T>
    std::tuple<T...> marshal(quint32 requestId, QDataStream& stream);

public:
    CCourseProcessor(int nPort);

public slots:
    virtual void slotNewConnection();
    void slotReadClient();
};



#endif // CCOURSEPROCESSOR_H
