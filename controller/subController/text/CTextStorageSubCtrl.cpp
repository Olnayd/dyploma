#include "CTextStorageSubCtrl.h"

#include <QDebug>
#include "database/CSqlConstants.h"
#include "database/query/SqlGetSchemaVersion.h"
#include "query/SqlTextStorageStatement.h"


CTextStorageSubCtrl::CTextStorageSubCtrl(std::shared_ptr<CSqlSubCtrl> sqlController)
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

        SqlTextStorageStatement stmtInitImage (EStorage::TEXT_STORAGE);
        if ( !mSqlController->executeQuery(stmtInitImage) )
        {
            qDebug()<< "[" << getName() << "]" << "re-creation of DB failed";
            return false;
        }
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
