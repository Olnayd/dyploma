#include "CDatabaseConnection.h"

#include <QDebug>

CDatabaseConnection::CDatabaseConnection(std::string name, std::string path, std::string databaseType)
   : mName(name)
   , mPath(path)
   , mDatabaseType(databaseType)
{

}

std::string CDatabaseConnection::getDatabaseDirPath()
{
    return mPath;
}
std::string CDatabaseConnection::getDatabasePath()
{
    return mPath + mName;
}

QSqlDatabase& CDatabaseConnection::getSqlDatabase()
{
    return mDatabase;
}


bool CDatabaseConnection::openConnection()
{
    mDatabase = QSqlDatabase::addDatabase(mDatabaseType.c_str(), std::string(mPath + mName).c_str());
    mDatabase.setDatabaseName(std::string(mPath + mName).c_str());


    if ( !mDatabase.open())
    {
        qDebug() << "Error. Cannot open database";
        return false;
    }

    return true ;
}

void CDatabaseConnection::closeConnection()
{
    mDatabase.close();
}



