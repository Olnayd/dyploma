#ifndef SQLCREATETEST_HPP
#define SQLCREATETEST_HPP

#include "SqlCreateLecture.hpp"
#include "database/query/SqlQuery.h"
#include "network/processor/course/types/Test.hpp"

class SqlCreateTest : public SqlQuery<quint32>
{
public:
    SqlCreateTest(const Test& test, const quint32 lectureId);
    SqlCreateTest(const Test& test, ::std::shared_ptr<SqlCreateLecture> queryCreateLecture);

private:
    virtual quint32 prepareResultOnError() override final;
    virtual quint32 prepareResultOnSuccess() override final;
    virtual QStringList preapareStatement() override final;

private:
    Test mTest;
    quint32 mLectureId;
    ::std::shared_ptr<SqlCreateLecture> mQueryCreateLecture;

};


#endif // SQLCREATETEST_HPP
