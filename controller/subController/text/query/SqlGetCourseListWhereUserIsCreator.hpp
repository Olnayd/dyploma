#ifndef SQLGETCOURSELISTWHEREUSERISCREATOR_H
#define SQLGETCOURSELISTWHEREUSERISCREATOR_H

#include "database/query/SqlQuery.h"
#include "network/processor/course/types/CourseListFilter.hpp"
#include "network/processor/course/types/CourseInformation.hpp"

class SqlGetCourseListWhereUserIsCreator : public SqlQuery<QVector<CourseInformation>>
{
public:
    SqlGetCourseListWhereUserIsCreator(const CourseListFilter& filter, const qint32 clientid);

private:
    virtual QVector<CourseInformation> prepareResultOnError() override final;
    virtual QVector<CourseInformation> prepareResultOnSuccess() override final;
    virtual QStringList preapareStatement() override final;
private:
    CourseListFilter mFilter;
    qint32 mClientId;
};

#endif // SQLGETCOURSELISTWHEREUSERISCREATOR_H
