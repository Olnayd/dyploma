#include "SqlCreateCourse.hpp"

SqlCreateCourse::SqlCreateCourse(const Course& courseInformation, const quint32 clientdatabaseId)
    : SqlQuery<quint32>(TEXT_STORAGE)
    , mCourseInformation(courseInformation)
    , mClientDatabaseId(clientdatabaseId)
{

}


QStringList SqlCreateCourse::preapareStatement()
{
    QStringList result;
    result.push_back( QString( "INSERT INTO Course(name, description) "
                               "VALUES (%1,%2); ").arg(mCourseInformation.name)
                                                  .arg(mCourseInformation.description));
    result.push_back( QString( "INSERT INTO CourseToListener (id_course, id_user)"
                               "SELECT last_insert_rowid(), %1;").arg(mClientDatabaseId));
    result.push_back( QString( "SELECT id_course FROM CourseToListener "
                               "WHERE rowid = last_insert_rowid();"));

    return result;
}

quint32 SqlCreateCourse::prepareResultOnError()
{
     return quint32();
}

quint32 SqlCreateCourse::prepareResultOnSuccess()
{
    quint32 result;
    while (next())
    {
        result = value(0).toInt();
    }
    return result;
}
