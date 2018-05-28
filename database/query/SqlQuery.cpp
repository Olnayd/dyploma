
#include "SqlQuery.h"
SqlQuery<void>::SqlQuery(EStorage destinationStorage)
    : QSqlQuery(CDatabaseConnectionFactory::getConnection(destinationStorage)->getSqlDatabase())
    , mDestinationStorage(destinationStorage)
{}

SqlQuery<void>::~SqlQuery()
{
    finish();
}

void SqlQuery<void>::prepareResult( )
{
    finish();
}
