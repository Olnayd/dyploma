#ifndef SQLGETALLCOURSES_H
#define SQLGETALLCOURSES_H

#include "database/query/SqlQuery.h"
#include "network/processor/course/types/CourseListFilter.hpp"
#include "network/processor/course/types/Course.hpp"

class SqlGetAllCourses : public SqlQuery<QVector<Course>>
{
public:
    SqlGetAllCourses(const CourseListFilter& filter);

private:
    virtual QVector<Course> prepareResultOnError() override final;
    virtual QVector<Course> prepareResultOnSuccess() override final;
    virtual QStringList preapareStatement() override final;
private:
    CourseListFilter mFilter;
};

#endif // SQLGETALLCOURSES_H
