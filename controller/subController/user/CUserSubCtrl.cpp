#include "CUserSubCtrl.h"
#include "query/SqlSignIn.hpp"
#include "query/SqlSignUp.hpp"

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

    SqlSignIn query(clientIdent);
    if(mSqlController->executeQuery(query))
    {
        reponseHandle.response_signIn(query.getResult(), responseContext);
    }
    else
        reponseHandle.response_error(2001, responseContext);


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
        reponseHandle.response_error(2002, responseContext);
}

void CUserSubCtrl::removeClient()
{
    CNetworkClient* pClient = (CNetworkClient*)sender();
    auto it = mClientList.find(pClient->getClientId());
    if (it != mClientList.end())
            mClientList.erase(it);
}
