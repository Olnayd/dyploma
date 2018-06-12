#include "CUserSubCtrl.h"
#include "query/SqlSignIn.hpp"
#include "query/SqlSignUp.hpp"
#include "network/processor/course/types/ErrorType.hpp"
#include "network/CNetworkClient.hpp"

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

ClientType CUserSubCtrl::getClientType(const quint32 clientId)
{
    auto it = mClientList.find(clientId);
    if (it != mClientList.end())
    {
        return it->second.getClientType();
    }
    return ClientType::Unknown;
}

bool CUserSubCtrl::isClientHasPermission(const quint32 clientId, const ClientType persmissions)
{
    auto it = mClientList.find(clientId);
    if (it != mClientList.end())
    {
        return it->second.isClientHasPermissions(persmissions);
    }
    return false;
}

qint32 CUserSubCtrl::getClientDatabaseId(const quint32 clientId)
{
    auto it = mClientList.find(clientId);
    if (it != mClientList.end())
    {
        return it->second.getClientDatabaseId();
    }
    return -1;
}


void CUserSubCtrl::signIn( const ClientIdentificator& clientIdent,
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
    it = mClientList.find(netwClient->getClientId());

    SqlSignIn query(clientIdent);
    if(mSqlController->executeQuery(query))
    {
        ClientInformation info = query.getResult();
        it->second.setClientType(info.type);
        it->second.setClientDatabaseId(query.getClientDatabaseId());
        reponseHandle.response_signIn(info, responseContext);
    }
    else
        reponseHandle.response_error(Error_Internal_Sql_Error, responseContext);


    //sql query
}

void CUserSubCtrl::signUp(const ClientIdentificator& clientIdent, const ClientInformation& clientInfo, const CResponseContext& responseContext, ICourseResponseHandle& reponseHandle)
{

    SqlSignUp query(clientIdent, clientInfo);
    if(mSqlController->executeQuery(query))
    {
        reponseHandle.response_signUp(query.getResult(), responseContext);
    }
    else
        reponseHandle.response_error(Error_Internal_Sql_Error, responseContext);
}

void CUserSubCtrl::removeClient()
{
    CNetworkClient* pClient = (CNetworkClient*)sender();
    auto it = mClientList.find(pClient->getClientId());
    if (it != mClientList.end())
            mClientList.erase(it);
}
