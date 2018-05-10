#include "SqlImageStorageStatement.h"
#include <QVariant>

#include <database/CSqlConstants.h>

SqlImageStorageStatement::SqlImageStorageStatement(EStorage storageType)
    : SqlQuery<void>(storageType)
{

}

QStringList SqlImageStorageStatement::preapareStatement()
{
    QStringList result;
    result.push_back( QString( "DROP TABLE IF EXISTS Version;" ) );
    result.push_back( QString( "CREATE TABLE IF NOT EXISTS Version( \
                                major INT,        \
                                minor INT);" ) );
    result.push_back( QString( "INSERT INTO Version  \
                                VALUES (%1, %2);").arg( database::constant::TextStorageVersion.major)
                                                  .arg( database::constant::TextStorageVersion.minor) );
    return result;
}

void SqlImageStorageStatement::prepareResultOnError()
{
    //dummy implementation
}
void SqlImageStorageStatement::prepareResultOnSuccess()
{
    //dummy implementation
}
