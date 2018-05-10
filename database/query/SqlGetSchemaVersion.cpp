#include "SqlGetSchemaVersion.h"

#include <QVariant>
#include <QDebug>

SqlGetSchemaVersion::SqlGetSchemaVersion(EStorage storageType)
    : SqlQuery<common::version>(storageType)
{

}

QStringList SqlGetSchemaVersion::preapareStatement()
{
    QStringList result;
    result.push_back( QString( "SELECT major, minor \
                                FROM Version;" ) );
    return result;
}

common::version SqlGetSchemaVersion::prepareResultOnError()
{
    return common::version(-1, -1);
}
common::version SqlGetSchemaVersion::prepareResultOnSuccess()
{
    if(next())
    {
        int major = value(0).toInt();
        int minor = value(1).toInt();
        return common::version(major, minor);
    }
    else
    {
        return common::version(-1, -1);
    }





}
