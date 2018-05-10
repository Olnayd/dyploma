#ifndef CSQLSUBCONTROLLER_H
#define CSQLSUBCONTROLLER_H

#include <map>
#include "database/connection/EStorage.h"
#include "database/query/SqlQuery.h"
#include "common/controller/CSubController.h"

class CSqlSubController : public common::controller::CSubController
{
public:

    CSqlSubController();
    template<typename T>
    bool executeQuery(SqlQuery<T>& query);
  //  template<typename T>
  //  void executeQuery(SqlQuery<T> query, std::function<void(bool result)>());


private:
    virtual bool init() override final;
    virtual const char* getName() override final;
    virtual bool prepareShutdown() override final;

private:
    ::std::map<EStorage, bool > mConnectionStatus;
};

template<typename T>
bool CSqlSubController::executeQuery(SqlQuery<T>& sqlQuery)
{
    QStringList stmtList = sqlQuery.preapareStatement();
    if (stmtList.empty()) return true;

    auto database = CDatabaseConnectionFactory::getConnection(sqlQuery.mDestinationStorage);
    sqlQuery.mQueryPtr =  new QSqlQuery(database->getSqlDatabase());


    //Transaction
    bool isExecutionFailed = false;
    database->getSqlDatabase().transaction();
    for (auto stmt : stmtList)
    {
        qDebug() << stmt.toStdString().c_str();
        if(!sqlQuery.mQueryPtr->exec(stmt))
        {
            isExecutionFailed = true;
            break;
             qDebug() << "CSqlSubController query execution failed. Start rollback";
            return database->getSqlDatabase().rollback();
        }
    }
    if (isExecutionFailed) {
        database->getSqlDatabase().rollback();
        return false;
    }
    else return database->getSqlDatabase().commit();

}
#endif // CSQLSUBCONTROLLER_H
