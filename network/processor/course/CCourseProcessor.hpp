#ifndef CCOURSEPROCESSOR_H
#define CCOURSEPROCESSOR_H

#include <memory>
#include <QTcpServer>

#include "ICourseResponseHandle.hpp"
#include "network/CNetworkClient.hpp"

class CCourseProcessor
        : public QObject
        , public ICourseResponseHandle
{
    Q_OBJECT
public:
    CCourseProcessor();
    bool start();

    virtual void getCourseInfo(const quint32 courseId, const CResponseContext& responseContext) = 0;
    virtual void autorization(const QString& login, const QString& password, const CResponseContext& responseContext) = 0;

    virtual void response_getCourseInfo(const CResponseContext& responseContext) override final;
    virtual void response_autorization(const bool result, const CResponseContext& responseContext) override final;
    virtual void response_error(const quint8 result, const CResponseContext& responseContext) override final;

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
