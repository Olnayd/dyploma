#include "CUserSubCtrl.h"

CUserSubCtrl::CUserSubCtrl( std::shared_ptr<CSqlSubCtrl> sqlController)
    : mSqlController( sqlController )
{

}

bool CUserSubCtrl::init()
{
    return true;
}

const char* CUserSubCtrl::getName()
{
    return "CUserSubCtrl";
}

bool CUserSubCtrl::prepareShutdown()
{
    return true;
}

bool CUserSubCtrl::isClientHasPermission(const quint32 clientId, const quint8 persmissions)
{
    auto it = mClientList.find(clientId);
    if (it != mClientList.end())
    {
        return it->second.isClientHasPermissions(persmissions);
    }
    return false;
}

void CUserSubCtrl::authorizeClient(const QString& login,
                                   const QString& password,
                                   const CResponseContext& responseContext,
                                   ICourseResponseHandle& reponseHandle)
{
    const ::std::shared_ptr<CNetworkClient>& netwClient = responseContext.clientPtr;
    connect(netwClient.get(), SIGNAL(disconnected()),
            this,               SLOT(removeClient()));

    auto it = mClientList.find(netwClient->getClientId());
    if (it == mClientList.end())
    {
        mClientList.insert(::std::make_pair(netwClient->getClientId(), ClientInfo(netwClient->getClientId())));
    }

    auto itTEMP = mClientList.find(netwClient->getClientId());
    if (itTEMP != mClientList.end())
        itTEMP->second.setClientPermissions(3);

    reponseHandle.response_autorization(true, responseContext);

    //sql query
}

void CUserSubCtrl::removeClient()
{
    CNetworkClient* pClient = (CNetworkClient*)sender();
    auto it = mClientList.find(pClient->getClientId());
    if (it != mClientList.end())
            mClientList.erase(it);
}
