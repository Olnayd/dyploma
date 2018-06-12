#ifndef SQLFINISHLECTURE_H
#define SQLFINISHLECTURE_H

#include "database/query/SqlQuery.h"

class SqlFinishLecture : public SqlQuery<bool>
{
public:
    SqlFinishLecture(const quint32 lectureId, const quint32 clientDatabaseId);

private:
    virtual bool prepareResultOnError() override final;
    virtual bool prepareResultOnSuccess() override final;
    virtual QStringList preapareStatement() override final;

private:
    quint32 mTestId;
    quint32 mClientDatabaseId;
};


#endif // SQLFINISHLECTURE_H
