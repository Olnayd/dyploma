#include "CCourseCtrl.h"

#include <map>
#include <QFileInfo>
#include <QDir>
#include "database/connection/EStorage.h"
#include "database/connection/CDatabaseConnectionFactory.h"
#include <QDebug>

CCourseCtrl::CCourseCtrl( )
    : mSqlController   ( std::make_shared<CSqlSubController>())
    , mTextController  ( std::make_shared<CTextStorageSubCtrl>(mSqlController))
    , mImageController ( std::make_shared<CImageStorageSubCtrl>(mSqlController))
{
    addSubCtrl(std::static_pointer_cast<common::controller::CSubController>(mSqlController));
    addSubCtrl(std::static_pointer_cast<common::controller::CSubController>(mTextController));
    addSubCtrl(std::static_pointer_cast<common::controller::CSubController>(mImageController));

}

bool CCourseCtrl::init()
{
    bool isStarted = start();
    qDebug() << "is started";
    qDebug() << isStarted;
    return true;
}

const char* CCourseCtrl::getName()
{
    return "CourseCtrl";
}

bool CCourseCtrl::prepareShutdown()
{
    return true;
}

/*virtual*/ void CCourseCtrl::autorization(const QString& login, const QString& password, const CResponseContext& responseContext)
{
    response_autorization( true, responseContext);
}

