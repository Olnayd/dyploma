#include "SqlTextStorageStatement.h"

#include <QVariant>
#include <QDebug>
#include <QString>
#include <database/CSqlConstants.h>

SqlTextStorageStatement::SqlTextStorageStatement(EStorage storageType)
    : SqlQuery<void>(storageType)
{

}

QStringList SqlTextStorageStatement::preapareStatement()
{
    qDebug() << "SqlTextStorageStatement::preapareStatement";
    QStringList result;
    result.reserve(3);
    result.push_back( QString( "DROP TABLE IF EXISTS Version;" ) );
    result.push_back( QString( "CREATE TABLE IF NOT EXISTS Version( \
                                major INT,        \
                                minor INT);" ) );
    result.push_back( QString( "INSERT INTO Version  \
                                VALUES (%1, %2);").arg( database::constant::TextStorageVersion.major)
                                                  .arg( database::constant::TextStorageVersion.minor) );
    return result;
}

void SqlTextStorageStatement::prepareResultOnError()
{
    //dummy implementation
}
void SqlTextStorageStatement::prepareResultOnSuccess()
{
    //dummy implementation
}

