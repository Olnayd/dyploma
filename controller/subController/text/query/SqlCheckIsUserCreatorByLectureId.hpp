#ifndef SQLCHECKISUSERCREATORBYLECTUREID_H
#define SQLCHECKISUSERCREATORBYLECTUREID_H

#include "database/query/SqlQuery.h"

class SqlCheckIsUserCreatorByLectureId : public SqlQuery<bool>
{
public:
    SqlCheckIsUserCreatorByLectureId(const qint32 clientDatabaseId, const quint32 lectureId);

private:
    virtual bool prepareResultOnError() override final;
    virtual bool prepareResultOnSuccess() override final;
    virtual QStringList preapareStatement() override final;

private:
    qint32 mClientDatabaseId;
    quint32 mLectureId;
};

#endif // SQLCHECKISUSERCREATORBYLECTUREID_H
