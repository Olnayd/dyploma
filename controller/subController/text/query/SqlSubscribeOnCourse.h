#ifndef SQLSUBSCRIBEONCOURSE_H
#define SQLSUBSCRIBEONCOURSE_H

#include "database/query/SqlQuery.h"

class SqlSubscribeOnCourse : public SqlQuery<bool>
{
public:
    SqlSubscribeOnCourse(const quint32 courseId, const quint32 clientdatabaseId);

private:
    virtual bool prepareResultOnError() override final;
    virtual bool prepareResultOnSuccess() override final;
    virtual QStringList preapareStatement() override final;

private:
    quint32 mCourseId;
    qint32 mClientDatabaseId;
};


#endif // SQLSUBSCRIBEONCOURSE_H
