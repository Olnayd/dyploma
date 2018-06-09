#include "SqlCreateLecture.hpp"

SqlCreateLecture::SqlCreateLecture(const Lecture& lecture)
    : SqlQuery<quint32>(TEXT_STORAGE)
    , mLecture(lecture)
{

}

QStringList SqlCreateLecture::preapareStatement()
{
    QStringList result;
    result.push_back( QString( "INSERT INTO Lecture(name, data) "
                               "VALUES (%1,%2); ").arg(mLecture.NameByRef())
                                                  .arg(mLecture.DataByRef()));
    result.push_back( QString( "SELECT last_insert_rowid();"));

    return result;
}

quint32 SqlCreateLecture::prepareResultOnError()
{
     return quint32(-1);
}

quint32 SqlCreateLecture::prepareResultOnSuccess()
{
    quint32 result(-1);
    while (next())
    {
        result = value(0).toInt();
    }
    return result;
}
