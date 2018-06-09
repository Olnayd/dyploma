#ifndef SQLCHECKISLECTUREISDONE_H
#define SQLCHECKISLECTUREISDONE_H

#include "database/query/SqlQuery.h"

class SqlCheckIsLectureIsDone : public SqlQuery<bool>
{
public:
    SqlCheckIsLectureIsDone(const qint32 clientDatabaseId, const quint32 lectureId);

private:
    virtual bool prepareResultOnError() override final;
    virtual bool prepareResultOnSuccess() override final;
    virtual QStringList preapareStatement() override final;

private:
    qint32 mClientDatabaseId;
    quint32 mLectureId;
};


#endif // SQLCHECKISLECTUREISDONE_H
