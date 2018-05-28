#include "CImageStorageSubCtrl.h"

#include "database/CSqlConstants.h"
#include "database/query/SqlGetSchemaVersion.h"
#include "database/query/SqlImageStorageStatement.h"

#include <QDebug>

CImageStorageSubCtrl::CImageStorageSubCtrl( std::shared_ptr<CSqlSubCtrl> sqlController)
    : mSqlController( sqlController )
{

}

bool CImageStorageSubCtrl::init()
{
    SqlGetSchemaVersion stmt (EStorage::IMAGE_STORAGE) ;
    mSqlController->executeQuery(stmt);
    common::version dbVersion = stmt.getResult();

    if ( database::constant::TextStorageVersion != dbVersion)
    {
        qDebug()<< "[" << getName() << "]"
                << "different database versions. Expected"
                << database::constant::TextStorageVersion.major
                << ":"
                << database::constant::TextStorageVersion.minor
                << "but"
                << dbVersion.major
                << ":"
                << dbVersion.minor
                << "is come.";

        SqlImageStorageStatement stmtInitImage (EStorage::IMAGE_STORAGE);
        if ( !mSqlController->executeQuery(stmtInitImage) )
        {
            qDebug()<< "[" << getName() << "]" << "re-creation of DB failed";
            return false;
        }

     }
    return true;
}

const char* CImageStorageSubCtrl::getName()
{
    return "CImageStorageSubCtrl";
}

bool CImageStorageSubCtrl::prepareShutdown()
{
    return true;
}
