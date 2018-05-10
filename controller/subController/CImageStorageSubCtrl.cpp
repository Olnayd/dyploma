#include "CImageStorageSubCtrl.h"

#include "database/CSqlConstants.h"
#include "database/query/SqlGetSchemaVersion.h"
#include "database/query/SqlImageStorageStatement.h"

#include <QDebug>

CImageStorageSubCtrl::CImageStorageSubCtrl( std::shared_ptr<CSqlSubController> sqlController)
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
        SqlImageStorageStatement stmtInitImage (EStorage::IMAGE_STORAGE);
        if ( !mSqlController->executeQuery(stmtInitImage) )
            qDebug()<< "CImageStorageSubCtrl Query execution failed";
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
