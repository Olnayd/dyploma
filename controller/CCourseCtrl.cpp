#include "CCourseCtrl.h"

#include <map>
#include <QFileInfo>
#include <QDir>
#include "database/connection/EStorage.h"
#include "database/connection/CDatabaseConnectionFactory.h"
#include <QDebug>

#include "network/processor/course/types/ClientType.hpp"
#include "network/processor/course/types/ErrorType.hpp"

CCourseCtrl::CCourseCtrl( )
    : mSqlController   ( std::make_shared<CSqlSubCtrl>())
    , mTextController  ( std::make_shared<CTextStorageSubCtrl>(mSqlController))
    , mImageController ( std::make_shared<CImageStorageSubCtrl>(mSqlController))
    , mUserController  ( std::make_shared<CUserSubCtrl>(mSqlController))
{
    addSubCtrl(std::static_pointer_cast<common::controller::CSubController>(mSqlController));
    addSubCtrl(std::static_pointer_cast<common::controller::CSubController>(mTextController));
    addSubCtrl(std::static_pointer_cast<common::controller::CSubController>(mImageController));
    addSubCtrl(std::static_pointer_cast<common::controller::CSubController>(mUserController));

}

bool CCourseCtrl::init()
{
    return start();
}

const char* CCourseCtrl::getName()
{
    return "CourseCtrl";
}

bool CCourseCtrl::prepareShutdown()
{
    return true;
}

/*virtual*/ void CCourseCtrl::getCourseInfo(const quint32 courseId, const CResponseContext& responseContext)
{
    if (mUserController->isClientHasPermission( responseContext.clientPtr->getClientId(), Student ))
    {
        response_getCourseInfo(responseContext);
    }
    else
        response_error(Error_WTF, responseContext);


}

/*virtual*/ void CCourseCtrl::signIn(const ClientIdentificator &clientIdent, const CResponseContext &responseContext)
{
    mUserController->signIn(clientIdent, responseContext, *this);
}

/*virtual*/ void CCourseCtrl::signUp(const ClientIdentificator &clientIdent,const ClientInformation& clientInfo, const CResponseContext &responseContext)
{
    mUserController->signUp(clientIdent, clientInfo, responseContext, *this);
}
