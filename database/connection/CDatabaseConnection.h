#ifndef CDatabaseConnection_H
#define CDatabaseConnection_H

#include <QtSql/QSqlDatabase>
class QSqlDatabase;

class CDatabaseConnection
{
public:
    CDatabaseConnection( std::string name, std::string path, std::string databaseType );
    ~CDatabaseConnection() = default;
    bool openConnection();
    void closeConnection();


    std::string         getDatabasePath();
    std::string         getDatabaseDirPath();
    QSqlDatabase&       getSqlDatabase();

private:

    std::string mName;
    std::string mPath;
    std::string mDatabaseType;

    QSqlDatabase mDatabase;

};

#endif // CDatabaseConnection_H
