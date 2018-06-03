#include "SqlGetCourseListWhereUserIsCreator.hpp"

SqlGetCourseListWhereUserIsCreator::SqlGetCourseListWhereUserIsCreator(const CourseListFilter& filter, const qint32 clientid)
    : SqlQuery<QVector<CourseInformation>>(TEXT_STORAGE)
    , mFilter(filter)
    , mClientId(clientid)
{

}

QStringList SqlGetCourseListWhereUserIsCreator::preapareStatement()
{
    QStringList result;
    result.push_back( QString( "SELECT id, name, description FROM CourseToCreator"
                               "INNER JOIN CourseToListener ON id_course = id"
                               "WHERE id_user = %1").arg(mClientId) );
    return result;
}

QVector<CourseInformation> SqlGetCourseListWhereUserIsCreator::prepareResultOnError()
{
    return QVector<CourseInformation>();
}

QVector<CourseInformation> SqlGetCourseListWhereUserIsCreator::prepareResultOnSuccess()
{
    QVector<CourseInformation> result;
    while (next())
    {
        quint32 id = value(0).toInt();
        QString name = value(1).toString();
        QString description = value(2).toString();
        result.push_back(CourseInformation(id, name, description));
    }
    return result;
}
