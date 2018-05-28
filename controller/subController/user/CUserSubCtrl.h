#ifndef CUSERSUBCONTROLLER_H
#define CUSERSUBCONTROLLER_H

#include <QObject>
#include "network/processor/course/ICourseResponseHandle.hpp"
#include "network/CNetworkClient.hpp"
#include "controller/subController/CSqlSubCtrl.h"
#include "common/controller/CSubController.h"

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
    bool isClientHasPermission(const quint32 clientId, const quint8 persmissions);

    void signIn(const ClientIdentificator& clientIdent, const CResponseContext& responseContext, ICourseResponseHandle& reponseHandle);
    void signUp(const ClientIdentificator& clientIdent, const ClientInformation& clientInfo, const CResponseContext& responseContext, ICourseResponseHandle& reponseHandle);

private slots:
    void removeClient();
private:
    struct ClientInfo
    {
        ClientInfo(const quint32 clientId)
            : mClientId(clientId), mClientRights(0) {}
        void setClientPermissions(const quint8 clientRights)
        {
            mClientRights = clientRights;
        }

        bool isClientHasPermissions(const quint8 rights)
        {
            return mClientRights & rights;
        }

    private:
        quint32 mClientId;
        quint8  mClientRights;
    };

    std::map<quint32, ClientInfo> mClientList;
    std::shared_ptr<CSqlSubCtrl> mSqlController;
};

#endif // CUSERSUBCONTROLLER_H
