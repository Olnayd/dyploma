#ifndef SQLCHECKISUSERLISTENER_H
#define SQLCHECKISUSERLISTENER_H

#include "database/query/SqlQuery.h"

class SqlCheckIsUserListener : public SqlQuery<bool>
{
public:
    SqlCheckIsUserListener(const qint32 clientDatabaseId, const quint32 courseId);

private:
    virtual bool prepareResultOnError() override final;
    virtual bool prepareResultOnSuccess() override final;
    virtual QStringList preapareStatement() override final;

private:
    qint32 mClientDatabaseId;
    quint32 mCourseId;
};
#endif // SQLCHECKISUSERLISTENER_H
