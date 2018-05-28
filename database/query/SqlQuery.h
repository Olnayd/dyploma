#ifndef SQLQUERY_H
#define SQLQUERY_H

#include <QtSql/qsqlquery.h>
#include <QSqlError>
#include <QVariant>
#include <cassert>
#include "database/connection/EStorage.h"
#include "database/connection/CDatabaseConnectionFactory.h"

class CSqlSubCtrl;

template<typename RETERN_TYPE>
class SqlQuery : private QSqlQuery
{
    friend CSqlSubCtrl;
public:
    SqlQuery( EStorage destinationStorage );
    ~SqlQuery( );
    bool isErrorOccured();

    RETERN_TYPE getResult() const;

protected:
    using QSqlQuery::next;
    using QSqlQuery::finish;
    using QSqlQuery::value;



private:
//    bool isErrorOccured();


    //called after execution of query
    void prepareResult();
    virtual RETERN_TYPE prepareResultOnSuccess() = 0;
    virtual RETERN_TYPE prepareResultOnError() = 0;
    virtual QStringList preapareStatement() = 0;
private:
    EStorage mDestinationStorage;
    RETERN_TYPE mResult;
};

template<typename RETERN_TYPE>
SqlQuery<RETERN_TYPE>::~SqlQuery()
{
    finish();
}

template<typename RETERN_TYPE>
SqlQuery<RETERN_TYPE>::SqlQuery(EStorage destinationStorage)
    : QSqlQuery(CDatabaseConnectionFactory::getConnection(destinationStorage)->getSqlDatabase())
    , mDestinationStorage{destinationStorage}
    , mResult()
{}

template<typename RETERN_TYPE>
bool SqlQuery<RETERN_TYPE>::isErrorOccured( )
{
    return lastError().isValid();
}

template<typename RETERN_TYPE>
void SqlQuery<RETERN_TYPE>::prepareResult( )
{
    mResult = isErrorOccured() ? prepareResultOnError() : prepareResultOnSuccess();
    finish();
}

template<typename RETERN_TYPE>
RETERN_TYPE SqlQuery<RETERN_TYPE>::getResult( ) const
{
    return mResult;
}


template<>
class SqlQuery<void> : private QSqlQuery
{
        friend CSqlSubCtrl;
public:
    SqlQuery( EStorage destinationStorage );
    ~SqlQuery( );

    using QSqlQuery::next;
    using QSqlQuery::finish;
    using QSqlQuery::value;
private:

    //called after execution of query
    void prepareResult();
    virtual void prepareResultOnSuccess() = 0;
    virtual void prepareResultOnError() = 0;
    virtual QStringList preapareStatement() = 0;
private:
    EStorage mDestinationStorage;
};


#endif // SQLQUERY_H
