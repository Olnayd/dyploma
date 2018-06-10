#ifndef SQLGETTEST_H
#define SQLGETTEST_H

#include "database/query/SqlQuery.h"
#include "network/processor/course/types/test/Test.hpp"


class SqlGetTest : public SqlQuery<Test>
{
public:
    SqlGetTest(const quint32 lectureId);

private:
    virtual Test prepareResultOnError() override final;
    virtual Test prepareResultOnSuccess() override final;
    virtual QStringList preapareStatement() override final;

private:
    quint32 mLectureId;

public:
    QString data;
};



#endif // SQLGETTEST_H
