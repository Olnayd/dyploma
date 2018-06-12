#include "CCourseCtrl.hpp"

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
        response_error(Error_User_Does_Not_Has_Permissions, responseContext);
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
        response_error(Error_User_Does_Not_Has_Permissions, responseContext);
}

/*virtual*/ void CCourseCtrl::subscribeOnCourse(const quint32 courseid, const CResponseContext& responseContext)
{
    if (mUserController->isClientHasPermission( responseContext.clientPtr->getClientId(), Student ))
    {
        mTextController->subscribeOnCourse(mUserController->getClientDatabaseId(responseContext.clientPtr->getClientId()), courseid, responseContext, *this);
    }
    else
        response_error(Error_User_Does_Not_Has_Permissions, responseContext);
}

/*virtual*/ void CCourseCtrl::createCourse( const Course& courseInfo, const CResponseContext& responseContext)
{
    if (mUserController->isClientHasPermission( responseContext.clientPtr->getClientId(), Teacher ))
    {
        mTextController->createCourse(mUserController->getClientDatabaseId(responseContext.clientPtr->getClientId()), courseInfo, responseContext, *this);
    }
    else
        response_error(Error_User_Does_Not_Has_Permissions, responseContext);
}

/*virtual*/ void CCourseCtrl::createLecture( const quint32 courseId, const Lecture& lecture, const CResponseContext& responseContext)
{
    if (mUserController->isClientHasPermission( responseContext.clientPtr->getClientId(), Teacher ))
    {
        mTextController->createLecture(mUserController->getClientDatabaseId(responseContext.clientPtr->getClientId()), courseId,  lecture, responseContext, *this);
    }
    else
        response_error(Error_User_Does_Not_Has_Permissions, responseContext);
}
/*virtual*/ void CCourseCtrl::createTest( const quint32 lectureId, const Test& test, const CResponseContext& responseContext)
{
    if (mUserController->isClientHasPermission( responseContext.clientPtr->getClientId(), Teacher ))
    {
       mTextController->createTest(mUserController->getClientDatabaseId(responseContext.clientPtr->getClientId()),lectureId,  test, responseContext, *this);
    }
    else
        response_error(Error_User_Does_Not_Has_Permissions, responseContext);
}

/*virtual*/ void CCourseCtrl::getTest(const quint32 lectureId, const CResponseContext& responseContext)
{
    if (mUserController->isClientHasPermission( responseContext.clientPtr->getClientId(), Student ))
    {
        mTextController->getTest(mUserController->getClientDatabaseId(responseContext.clientPtr->getClientId()),
                                 mUserController->getClientType(responseContext.clientPtr->getClientId()),
                                 lectureId, responseContext, *this);
    }
    else
        response_error(Error_User_Does_Not_Has_Permissions, responseContext);

}


/*virtual*/ void CCourseCtrl::getLecture(const quint32 lectureId, const CResponseContext& responseContext)
{
    if (mUserController->isClientHasPermission( responseContext.clientPtr->getClientId(), Teacher ))
    {
        mTextController->getLecture(mUserController->getClientDatabaseId(responseContext.clientPtr->getClientId()),
                                    mUserController->getClientType(responseContext.clientPtr->getClientId()),lectureId, responseContext, *this);
    }
    else
        response_error(Error_User_Does_Not_Has_Permissions, responseContext);
}

/*virtual*/ void CCourseCtrl::getLecturePreviewList(const quint32 courseId, const CResponseContext& responseContext)
{
    if (mUserController->isClientHasPermission( responseContext.clientPtr->getClientId(), Teacher ))
    {
        mTextController->getLecturePreviewList(mUserController->getClientDatabaseId(responseContext.clientPtr->getClientId()),
                                               mUserController->getClientType(responseContext.clientPtr->getClientId()), courseId, responseContext, *this );
    }
    else
        response_error(Error_User_Does_Not_Has_Permissions, responseContext);
}

/*virtual*/ void CCourseCtrl::finishTest(const TestUserAnswers& userAnswears, const CResponseContext& responseContext)
{
    if (mUserController->isClientHasPermission( responseContext.clientPtr->getClientId(), Student ))
    {
        mTextController->finishTest(mUserController->getClientDatabaseId(responseContext.clientPtr->getClientId()),
                                    userAnswears, responseContext, *this );
    }
    else
        response_error(Error_User_Does_Not_Has_Permissions, responseContext);
}

/*virtual*/ void CCourseCtrl::finishLecture(const quint32 lectureId, const CResponseContext& responseContext)
{
    if (mUserController->isClientHasPermission( responseContext.clientPtr->getClientId(), Student ))
    {
        mTextController->finishLecture(mUserController->getClientDatabaseId(responseContext.clientPtr->getClientId()),
                                               lectureId, responseContext, *this );
    }
    else
        response_error(Error_User_Does_Not_Has_Permissions, responseContext);
}

/*virtual*/ void CCourseCtrl::signIn(const ClientIdentificator &clientIdent, const CResponseContext &responseContext)
{
    mUserController->signIn(clientIdent, responseContext, *this);
}

/*virtual*/ void CCourseCtrl::signUp(const ClientIdentificator &clientIdent,const ClientInformation& clientInfo, const CResponseContext &responseContext)
{
    mUserController->signUp(clientIdent, clientInfo, responseContext, *this);
}
