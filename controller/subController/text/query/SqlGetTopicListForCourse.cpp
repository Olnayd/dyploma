#include "SqlGetTopicListForCourse.hpp"

SqlGetTopicListForCourse::SqlGetTopicListForCourse(const quint32 courseId)
    : SqlQuery<QVector<CourseTopic>>(TEXT_STORAGE)
    , mCourseId(courseId)
{

}

QStringList SqlGetTopicListForCourse::preapareStatement()
{
    QStringList result;
    result.push_back( QString( "SELECT id_topic, name FROM TopicToCourse "
                               "INNER JOIN Topic ON TopicToCourse.id_topic = Topic.id "
                               "WHERE TopicToCourse.id_course=%1;").arg(mCourseId));

    return result;
}

QVector<CourseTopic> SqlGetTopicListForCourse::prepareResultOnError()
{
    return QVector<CourseTopic>();
}

QVector<CourseTopic> SqlGetTopicListForCourse::prepareResultOnSuccess()
{
    QVector<CourseTopic> result;
    while (next())
    {
        quint32 id = value(0).toInt();
        QString name = value(1).toString();
        result.push_back(CourseTopic(id, name));
    }
    return result;
}
