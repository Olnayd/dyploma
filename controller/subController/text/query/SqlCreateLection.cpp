#include "SqlCreateLection.hpp"

SqlCreateLection::SqlCreateLection(const LectionInformation& courseInformation, const quint32 courseId)
    : SqlQuery<quint32>(TEXT_STORAGE)
    , mLectionInformation(courseInformation)
    , mCourseId(courseId)
{

}

QStringList SqlCreateLection::preapareStatement()
{
    QStringList result;
    result.push_back( QString( "INSERT INTO Course(name, description, data) "
                               "VALUES (%1,%2,%3); ").arg(mLectionInformation.name)
                                                     .arg(mLectionInformation.description)
                                                     .arg(mLectionInformation.data));
    result.push_back( QString( "INSERT INTO CourseToCreator (id_lection, id_course )"
                               "SELECT last_insert_rowid(), %1;").arg(mCourseId));
    result.push_back( QString( "SELECT id_lection FROM CourseToCreator "
                               "WHERE rowid = last_insert_rowid();"));

    return result;
}

quint32 SqlCreateLection::prepareResultOnError()
{
     return quint32();
}

quint32 SqlCreateLection::prepareResultOnSuccess()
{
    quint32 result;
    while (next())
    {
        result = value(0).toInt();
    }
    return result;
}
