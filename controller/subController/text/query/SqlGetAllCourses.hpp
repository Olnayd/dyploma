#ifndef SQLGETALLCOURSES_H
#define SQLGETALLCOURSES_H

#include "database/query/SqlQuery.h"
#include "network/processor/course/types/CourseListFilter.hpp"
#include "network/processor/course/types/CourseInformation.hpp"

class SqlGetAllCourses : public SqlQuery<QVector<CourseInformation>>
{
public:
    SqlGetAllCourses(const CourseListFilter& filter);

private:
    virtual QVector<CourseInformation> prepareResultOnError() override final;
    virtual QVector<CourseInformation> prepareResultOnSuccess() override final;
    virtual QStringList preapareStatement() override final;
private:
    CourseListFilter mFilter;
};

#endif // SQLGETALLCOURSES_H
