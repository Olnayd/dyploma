#ifndef CCOURSEPROCESSOR_H
#define CCOURSEPROCESSOR_H

#include <memory>
#include <QTcpServer>

#include "network/CNetworkClient.hpp"
#include "network/CResponseContext.hpp"

class CCourseProcessor : public QObject
{
    Q_OBJECT
public:
    CCourseProcessor();
    bool start();

    virtual void autorization(const QString& login, const QString& password, const CResponseContext& responseContext) = 0;

    void response_autorization(const bool result, const CResponseContext& responseContext);

private:

    void sendToClient(QTcpSocket* pSocket, const quint32 requestid, const quint32 seqId);

public slots:
    void slotRemoveConnection();
    void slotNewConnection();
    void slotReadClient();

private:
    QTcpServer* m_ptcpServer;
    quint16     m_nNextBlockSize;
    std::map<quint32, ::std::shared_ptr<CNetworkClient>> mClientList;


};



#endif // CCOURSEPROCESSOR_H
