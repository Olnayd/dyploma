#ifndef SQLCHECKISUSERCREATOR_H
#define SQLCHECKISUSERCREATOR_H

#include "database/query/SqlQuery.h"

class SqlCheckIsUserCreatorByCourseId : public SqlQuery<bool>
{
public:
    SqlCheckIsUserCreatorByCourseId(const qint32 clientDatabaseId, const quint32 courseId);

private:
    virtual bool prepareResultOnError() override final;
    virtual bool prepareResultOnSuccess() override final;
    virtual QStringList preapareStatement() override final;

private:
    qint32 mClientDatabaseId;
    quint32 mCourseId;
};

#endif // SQLCHECKISUSERCREATOR_H
