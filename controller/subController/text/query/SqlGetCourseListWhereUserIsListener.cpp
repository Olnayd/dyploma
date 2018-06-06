#include "SqlGetCourseListWhereUserIsListener.hpp"

SqlGetCourseListWhereUserIsListener::SqlGetCourseListWhereUserIsListener(const CourseListFilter& filter, const qint32 clientid)
    : SqlQuery<QVector<Course>>(TEXT_STORAGE)
    , mFilter(filter)
    , mClientId(clientid)
{

}

QStringList SqlGetCourseListWhereUserIsListener::preapareStatement()
{
    QStringList result;
    result.push_back( QString( "SELECT id, name, description FROM Course"
                               "INNER JOIN CourseToListener ON id_course = id"
                               "WHERE id_user = %1").arg(mClientId) );
    return result;
}

QVector<Course> SqlGetCourseListWhereUserIsListener::prepareResultOnError()
{
    return QVector<Course>();
}

QVector<Course> SqlGetCourseListWhereUserIsListener::prepareResultOnSuccess()
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
