#ifndef CSQLSUBCONTROLLER_H
#define CSQLSUBCONTROLLER_H

#include<memory>
#include <QVector>
#include <map>
#include "database/connection/EStorage.h"
#include "database/query/SqlQuery.h"
#include "common/controller/CSubController.h"

class CSqlSubCtrl : public common::controller::CSubController
{
public:

    CSqlSubCtrl();
    template<typename T>
    bool executeQuery(SqlQuery<T>& query);

    template<typename T>
    bool executeQueryList(QVector<std::shared_ptr<SqlQuery<T>>>& queryList);
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
 bool CSqlSubCtrl::executeQueryList(QVector<std::shared_ptr<SqlQuery<T>>>& queryList)
{

    if(false == queryList.empty())
    {
        bool isExecutionFailed = false;
        auto destinationStorage = queryList.at(0)->mDestinationStorage;
        auto database = CDatabaseConnectionFactory::getConnection(destinationStorage);
        database->getSqlDatabase().transaction();

        for (std::shared_ptr<SqlQuery<T>> sqlQuery : queryList)
        {

            if (sqlQuery->mDestinationStorage != destinationStorage )
            {
                qDebug() << "[SQL]" << "Warning! Qurery ot another database";
                continue;
            }
            QStringList stmtList = sqlQuery->preapareStatement();
            if (stmtList.empty()) continue;


            qDebug() << "[SQL]" << "Start transaction";
            for (QString stmt : stmtList)
            {
                QString toTrace = stmt;
                qDebug() << "[SQL]" << toTrace.replace(" ", "").toStdString().data();
                if(!sqlQuery->exec(stmt)){ isExecutionFailed = true; break;}
            }
            if (isExecutionFailed) break;
            sqlQuery->prepareResult();
        }

        if (isExecutionFailed) {
            qDebug() << "[SQL]" << "Transaction failed, start rollback";
            database->getSqlDatabase().rollback();
            return false;
        }

        qDebug() << "[SQL]" << "Commit transaction";
        database->getSqlDatabase().commit();
    }
    return true;
}

template<typename T>
bool CSqlSubCtrl::executeQuery(SqlQuery<T>& sqlQuery)
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
