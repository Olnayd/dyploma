#include "SqlGetAllCourses.hpp"

SqlGetAllCourses::SqlGetAllCourses(const CourseListFilter& filter)
    : SqlQuery<QVector<Course>>(TEXT_STORAGE)
    , mFilter(filter)
{

}

QStringList SqlGetAllCourses::preapareStatement()
{
    QStringList result;
    result.push_back( QString( "SELECT id, name, description FROM Course" ) );
    return result;
}

QVector<Course> SqlGetAllCourses::prepareResultOnError()
{
    return QVector<Course>();
}

QVector<Course> SqlGetAllCourses::prepareResultOnSuccess()
{
    QVector<Course> result;
    while (next())
    {
        quint32 id = value(0).toInt();
        QString name = value(1).toString();
        QString description = value(2).toString();
        result.push_back(Course(id, name, description));
    }
    return result;
}
