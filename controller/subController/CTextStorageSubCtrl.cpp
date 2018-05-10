#include "CTextStorageSubCtrl.h"

#include <QDebug>
#include "database/CSqlConstants.h"
#include "database/query/SqlGetSchemaVersion.h"
#include "database/query/SqlTextStorageStatement.h"


CTextStorageSubCtrl::CTextStorageSubCtrl(std::shared_ptr<CSqlSubController> sqlController)
     : mSqlController( sqlController )
{

}

bool CTextStorageSubCtrl::init()
{
    SqlGetSchemaVersion stmt (EStorage::TEXT_STORAGE) ;
    mSqlController->executeQuery(stmt);
    common::version dbVersion = stmt.getResult();

    if ( database::constant::TextStorageVersion != dbVersion)
    {
        SqlTextStorageStatement stmtInitImage (EStorage::TEXT_STORAGE);
        if ( !mSqlController->executeQuery(stmtInitImage) )
            qDebug()<< "CTextStorageSubCtrl Query execution failed";
    }
    return true;
}

const char* CTextStorageSubCtrl::getName()
{
    return "CTextStorageSubCtrl";
}

bool CTextStorageSubCtrl::prepareShutdown()
{
    return true;
}
