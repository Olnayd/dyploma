#ifndef SQLCREATELECTION_H
#define SQLCREATELECTION_H

#include "database/query/SqlQuery.h"
#include "network/processor/course/types/CourseInformation.hpp"

class SqlCreateLection : public SqlQuery<quint32>
{
public:
    SqlCreateLection(const CourseInformation& courseInformation, const quint32 clientdatabaseId);

private:
    virtual quint32 prepareResultOnError() override final;
    virtual quint32 prepareResultOnSuccess() override final;
    virtual QStringList preapareStatement() override final;

private:
    CourseInformation mCourseInformation;
    qint32 mClientDatabaseId;
};

#endif // SQLCREATELECTION_H
