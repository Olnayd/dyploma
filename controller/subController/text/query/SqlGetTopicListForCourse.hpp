#ifndef SQLGETTOPICLISTFORCOURSE_H
#define SQLGETTOPICLISTFORCOURSE_H


#include <QVector>
#include "database/query/SqlQuery.h"
#include "network/processor/course/types/course/CourseTopic.hpp"

class SqlGetTopicListForCourse : public SqlQuery<QVector<CourseTopic>>
{
public:
    SqlGetTopicListForCourse(const quint32 courseId);

private:
    virtual QVector<CourseTopic> prepareResultOnError() override final;
    virtual QVector<CourseTopic> prepareResultOnSuccess() override final;
    virtual QStringList preapareStatement() override final;

private:
    quint32 mCourseId;
};

#endif // SQLGETTOPICLISTFORCOURSE_H
