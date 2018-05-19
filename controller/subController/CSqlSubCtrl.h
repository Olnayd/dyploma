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


    bool isExecutionFailed = false;

    ////Transaction
    database->getSqlDatabase().transaction();
    qDebug() << "[SQL]" << "Start transaction";
    for (QString stmt : stmtList)
    {
        QString toTrace = stmt;
        qDebug() << "[SQL]" << toTrace.replace(" ", "").toStdString().data();
        if(!sqlQuery.exec(stmt)){ isExecutionFailed = true; break;}
    }


    if (isExecutionFailed) {
        qDebug() << "[SQL]" << "Transaction failed, start rollback";
        database->getSqlDatabase().rollback();
        return false;
    }
    sqlQuery.prepareResult();
    qDebug() << "[SQL]" << "Commit transaction";
    database->getSqlDatabase().commit();
    ////

    return true;

}
#endif // CSQLSUBCONTROLLER_H
