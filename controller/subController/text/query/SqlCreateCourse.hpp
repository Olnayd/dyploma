#ifndef SQLCREATECOURSE_H
#define SQLCREATECOURSE_H

#include "database/query/SqlQuery.h"
#include "network/processor/course/types/course/Course.hpp"

class SqlCreateCourse : public SqlQuery<quint32>
{
public:
    SqlCreateCourse(const Course& courseInformation, const quint32 clientdatabaseId);

private:
    virtual quint32 prepareResultOnError() override final;
    virtual quint32 prepareResultOnSuccess() override final;
    virtual QStringList preapareStatement() override final;

private:
    Course mCourseInformation;
    qint32 mClientDatabaseId;
};


#endif // SQLCREATECOURSE_H
