#ifndef CUSERSUBCONTROLLER_H
#define CUSERSUBCONTROLLER_H

#include <QObject>
#include "controller/subController/CSqlSubCtrl.h"
#include "common/controller/CSubController.h"
#include "network/processor/course/types/ClientType.hpp"
#include "network/processor/course/ICourseResponseHandle.hpp"

class CUserSubCtrl
        : public QObject
        , public common::controller::CSubController

{
    Q_OBJECT
private:
    virtual bool init() override final;
    virtual const char* getName() override final;
    virtual bool prepareShutdown() override final;


public:
    CUserSubCtrl( std::shared_ptr<CSqlSubCtrl> sqlController );
    qint32 getClientDatabaseId(const quint32 clientId);
    ClientType getClientType(const quint32 clientId);
    bool isClientHasPermission(const quint32 clientId, const ClientType persmissions);


    void signIn(const ClientIdentificator& clientIdent, const CResponseContext& responseContext, ICourseResponseHandle& reponseHandle);
    void signUp(const ClientIdentificator& clientIdent, const ClientInformation& clientInfo, const CResponseContext& responseContext, ICourseResponseHandle& reponseHandle);

private slots:
    void removeClient();
private:
    struct ClientInfo
    {
        ClientInfo(const quint32 clientId)
            : mClientId(clientId), mClientDatabaseId(-1), mClientType(Unknown) {}

        void setClientType(const ClientType type)
        {
            mClientType = type;
        }

        void setClientDatabaseId(const quint32 id_)
        {
            mClientDatabaseId = id_;
        }

        bool isClientHasPermissions(const ClientType type) const
        {
            if (mClientType == Teacher ) return true;
            if (mClientType == Student && type == Student) return true;
            return false;
        }

        quint32 getClientDatabaseId() const
        {
            return mClientDatabaseId;
        }

        ClientType getClientType() const
        {
            return mClientType;
        }

    private:
        quint32 mClientId;
        qint32  mClientDatabaseId;
        ClientType  mClientType;
    };

    std::map<quint32, ClientInfo> mClientList;
    std::shared_ptr<CSqlSubCtrl> mSqlController;
};

#endif // CUSERSUBCONTROLLER_H
