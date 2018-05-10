#ifndef SQLQUERY_H
#define SQLQUERY_H

#include <QtSql/qsqlquery.h>
#include <QSqlError>
#include <QVariant>
#include <cassert>
#include "database/connection/EStorage.h"
#include "database/connection/CDatabaseConnectionFactory.h"

class CSqlSubController;

template<typename RETERN_TYPE>
class SqlQuery
{
    friend CSqlSubController;
public:
    SqlQuery( EStorage type );
    ~SqlQuery( );

    bool next();
    void finish();
    QVariant value( int pos );

    RETERN_TYPE getResult();

private:
    bool isErrorOccured();
    void prepareResult();
    virtual RETERN_TYPE prepareResultOnSuccess() = 0;
    virtual RETERN_TYPE prepareResultOnError() = 0;
    virtual QStringList preapareStatement() = 0;
private:
    EStorage   mDestinationStorage;
    QSqlQuery* mQueryPtr;
};

template<typename RETERN_TYPE>
SqlQuery<RETERN_TYPE>::~SqlQuery()
{
    if ( mQueryPtr != nullptr )
        mQueryPtr->finish();
    delete mQueryPtr;
}

template<typename RETERN_TYPE>
SqlQuery<RETERN_TYPE>::SqlQuery(EStorage storageType)
    : mDestinationStorage(storageType)
    , mQueryPtr(nullptr)
{}


template<typename RETERN_TYPE>
QVariant SqlQuery<RETERN_TYPE>::value(int pos)
{
    assert(mQueryPtr != nullptr);
    return mQueryPtr->value(pos);
}

template<typename RETERN_TYPE>
bool SqlQuery<RETERN_TYPE>::next()
{
    assert(mQueryPtr != nullptr);
    return mQueryPtr->next();
}

template<typename RETERN_TYPE>
void SqlQuery<RETERN_TYPE>::finish()
{
    assert(mQueryPtr != nullptr);
    return mQueryPtr->finish();
}

template<typename RETERN_TYPE>
bool SqlQuery<RETERN_TYPE>::isErrorOccured( )
{
    assert(mQueryPtr != nullptr);
    return mQueryPtr->lastError().isValid();
}

template<typename RETERN_TYPE>
RETERN_TYPE SqlQuery<RETERN_TYPE>::getResult( )
{
    assert(mQueryPtr != nullptr);
    if (isErrorOccured() || mQueryPtr->size() > 0)
    {
        //return getOnErrorResult();
    }
    else
    {
        //return getOnSuccessResult();
    }
    finish();
}





#endif // SQLQUERY_H
