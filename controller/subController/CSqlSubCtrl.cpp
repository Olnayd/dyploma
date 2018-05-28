#include "CSqlSubCtrl.h"

#include <QDir>
#include <QFileInfo>
#include <QSqlQuery>

#include "database/connection/CDatabaseConnectionFactory.h"

CSqlSubCtrl::CSqlSubCtrl()
    : mConnectionStatus( { ::std::make_pair<EStorage, bool> (EStorage::TEXT_STORAGE, false),
                           ::std::make_pair<EStorage, bool> (EStorage::IMAGE_STORAGE, false)})
{

}

bool CSqlSubCtrl::init()
{
    for (auto& pair : mConnectionStatus)
    {
        auto connection = CDatabaseConnectionFactory::getConnection(pair.first);
        {
            QFileInfo info( connection->getDatabasePath().c_str() );

            if ( !info.exists() )
            {
                QDir().mkpath( connection->getDatabaseDirPath().c_str() );
            }
        }
        pair.second = connection->openConnection();
    }
    return true;
}

bool CSqlSubCtrl::prepareShutdown()
{
    for (auto& pair : mConnectionStatus)
    {
        auto connection = CDatabaseConnectionFactory::getConnection(pair.first);
        connection->closeConnection();
    }
    return true;
}

const char* CSqlSubCtrl::getName()
{
    return "SqlSubController";
}

