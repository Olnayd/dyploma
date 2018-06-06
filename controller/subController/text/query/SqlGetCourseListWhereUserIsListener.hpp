#ifndef SQLGETCOURSELISTWHEREUSERISLISTENER_H
#define SQLGETCOURSELISTWHEREUSERISLISTENER_H

#include "database/query/SqlQuery.h"
#include "network/processor/course/types/CourseListFilter.hpp"
#include "network/processor/course/types/Course.hpp"

class SqlGetCourseListWhereUserIsListener : public SqlQuery<QVector<Course>>
{
public:
    SqlGetCourseListWhereUserIsListener(const CourseListFilter& filter, const qint32 clientid);

private:
    virtual QVector<Course> prepareResultOnError() override final;
    virtual QVector<Course> prepareResultOnSuccess() override final;
    virtual QStringList preapareStatement() override final;
private:
    CourseListFilter mFilter;
    qint32 mClientId;
};


#endif // SQLGETCOURSELISTWHEREUSERISLISTENER_H
