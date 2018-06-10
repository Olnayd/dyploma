#ifndef SQLCHECKISUSERLISTENERBYLECTUREID_H
#define SQLCHECKISUSERLISTENERBYLECTUREID_H

#include "database/query/SqlQuery.h"

class SqlCheckIsUserListenerByLectureId : public SqlQuery<bool>
{
public:
    SqlCheckIsUserListenerByLectureId(const qint32 clientDatabaseId, const quint32 lectureId);

private:
    virtual bool prepareResultOnError() override final;
    virtual bool prepareResultOnSuccess() override final;
    virtual QStringList preapareStatement() override final;

private:
    qint32 mClientDatabaseId;
    quint32 mLectureId;
};

#endif // SQLCHECKISUSERLISTENERBYLECTUREID_H
