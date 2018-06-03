#include "SqlGetTopicList.hpp"

SqlGetTopicList::SqlGetTopicList()
    : SqlQuery<QVector<CourseTopic>>(TEXT_STORAGE)
{

}

QStringList SqlGetTopicList::preapareStatement()
{
    QStringList result;
    result.push_back( QString( "SELECT id, name FROM Topic;" ) );
    return result;
}

QVector<CourseTopic> SqlGetTopicList::prepareResultOnError()
{
    return QVector<CourseTopic>();
}

QVector<CourseTopic> SqlGetTopicList::prepareResultOnSuccess()
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
