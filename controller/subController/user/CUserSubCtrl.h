#ifndef CUSERSUBCONTROLLER_H
#define CUSERSUBCONTROLLER_H

#include <QObject>
#include "network/processor/course/ICourseResponseHandle.hpp"
#include "network/CNetworkClient.hpp"
#include "controller/subController/CSqlSubCtrl.h"
#include "common/controller/CSubController.h"
#include "network/processor/course/types/ClientType.hpp"

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
    bool isClientHasPermission(const quint32 clientId, const ClientType persmissions);

    void signIn(const ClientIdentificator& clientIdent, const CResponseContext& responseContext, ICourseResponseHandle& reponseHandle);
    void signUp(const ClientIdentificator& clientIdent, const ClientInformation& clientInfo, const CResponseContext& responseContext, ICourseResponseHandle& reponseHandle);

private slots:
    void removeClient();
private:
    struct ClientInfo
    {
        ClientInfo(const quint32 clientId)
            : mClientId(clientId), mClientType(Unknown) {}

        void setClientType(const ClientType type)
        {
            mClientType = type;
        }

        bool isClientHasPermissions(const ClientType type)
        {
            if (mClientType == Teacher ) return true;
            if (mClientType == Student && type == Student) return true;
            return false;
        }

    private:
        quint32 mClientId;
        ClientType  mClientType;
    };

    std::map<quint32, ClientInfo> mClientList;
    std::shared_ptr<CSqlSubCtrl> mSqlController;
};

#endif // CUSERSUBCONTROLLER_H
