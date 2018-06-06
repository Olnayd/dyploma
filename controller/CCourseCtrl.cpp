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


/*virtual*/ void CCourseCtrl::getTopicList(const CResponseContext& responseContext)
{
    if (mUserController->isClientHasPermission( responseContext.clientPtr->getClientId(), Student ))
    {
        mTextController->getTopicList(responseContext, *this);
    }
    else
        response_error(Error_WTF, responseContext);
}
/*virtual*/ void CCourseCtrl::getCourseList( const CourseListWorkingType workType, const CResponseContext& responseContext)
{
    getCourseListByFilter(workType, CourseListFilter(CourseListFilterType::BY_NEWEST), responseContext);
}

/*virtual*/ void CCourseCtrl::getCourseListByFilter( const CourseListWorkingType workType, const CourseListFilter& filter, const CResponseContext& responseContext)
{
    bool isUserHasPermissions = false;
    switch(workType)
    {
    case ALL:
    case USER_IS_LISTENER:
        isUserHasPermissions = mUserController->isClientHasPermission( responseContext.clientPtr->getClientId(), Student );
        break;
    case USER_IS_CREATOR:
        isUserHasPermissions = mUserController->isClientHasPermission( responseContext.clientPtr->getClientId(), Teacher );
        break;
    }

    if (isUserHasPermissions)
    {
        mTextController->getCourseListByFilter(mUserController->getClientDatabaseId(responseContext.clientPtr->getClientId()), workType, filter, responseContext, *this);
    }
    else
        response_error(Error_WTF, responseContext);
}

/*virtual*/ void CCourseCtrl::subscribeOnCourse(const quint32 courseid, const CResponseContext& responseContext)
{
    if (mUserController->isClientHasPermission( responseContext.clientPtr->getClientId(), Student ))
    {
        mTextController->subscribeOnCourse(mUserController->getClientDatabaseId(responseContext.clientPtr->getClientId()), courseid, responseContext, *this);
    }
    else
        response_error(Error_WTF, responseContext);
}

/*virtual*/ void CCourseCtrl::createCourse( const Course& courseInfo, const CResponseContext& responseContext)
{
    if (mUserController->isClientHasPermission( responseContext.clientPtr->getClientId(), Teacher ))
    {
        mTextController->createCourse(mUserController->getClientDatabaseId(responseContext.clientPtr->getClientId()), courseInfo, responseContext, *this);
    }
    else
        response_error(Error_WTF, responseContext);
}

/*virtual*/ void CCourseCtrl::createLection( const quint32 courseid, const LectionInformation& lectionInfo, const CResponseContext& responseContext)
{
    if (mUserController->isClientHasPermission( responseContext.clientPtr->getClientId(), Teacher ))
    {
        mTextController->createLection(mUserController->getClientDatabaseId(responseContext.clientPtr->getClientId()), courseid,  lectionInfo, responseContext, *this);
    }
    else
        response_error(Error_WTF, responseContext);
}

/*virtual*/ void CCourseCtrl::getLection(const quint32 lectionId, const CResponseContext& responseContext)
{
    if (mUserController->isClientHasPermission( responseContext.clientPtr->getClientId(), Teacher ))
    {
        mTextController->getLection(mUserController->getClientDatabaseId(responseContext.clientPtr->getClientId()), lectionId, responseContext, *this);
    }
    else
        response_error(Error_WTF, responseContext);
}

/*virtual*/ void CCourseCtrl::getLectionPreviewList(const quint32 courseid, const CResponseContext& responseContext)
{
    if (mUserController->isClientHasPermission( responseContext.clientPtr->getClientId(), Teacher ))
    {
        mTextController->getLectionPreviewList(courseid, responseContext, *this );
    }
    else
        response_error(Error_WTF, responseContext);
}


///*virtual*/ void CCourseCtrl::getCourseInfo(const quint32 courseId, const CResponseContext& responseContext)
//{
//    if (mUserController->isClientHasPermission( responseContext.clientPtr->getClientId(), Student ))
//    {
//        response_getCourseInfo(responseContext);
//    }
//    else
//        response_error(Error_WTF, responseContext);


//}

/*virtual*/ void CCourseCtrl::signIn(const ClientIdentificator &clientIdent, const CResponseContext &responseContext)
{
    mUserController->signIn(clientIdent, responseContext, *this);
}

/*virtual*/ void CCourseCtrl::signUp(const ClientIdentificator &clientIdent,const ClientInformation& clientInfo, const CResponseContext &responseContext)
{
    mUserController->signUp(clientIdent, clientInfo, responseContext, *this);
}
