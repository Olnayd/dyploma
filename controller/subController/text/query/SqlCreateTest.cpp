#include "SqlCreateTest.hpp"
#include "SqlCreateLecture.hpp"

SqlCreateTest::SqlCreateTest(const Test& test, const quint32 lectureId)
    : SqlQuery<quint32>(TEXT_STORAGE)
    , mTest(test)
    , mLectureId(lectureId)
    ,mQueryCreateLecture ( nullptr )
{

}

SqlCreateTest::SqlCreateTest(const Test& test, ::std::shared_ptr<SqlCreateLecture> queryCreateLecture)
    : SqlQuery<quint32>(TEXT_STORAGE)
    , mTest(test)
    , mLectureId(-1)
    , mQueryCreateLecture(queryCreateLecture)
{

}



QStringList SqlCreateTest::preapareStatement()
{
    QStringList result;
    result.push_back( QString( "INSERT INTO Test(id, name ) "
                               "VALUES (%1,%2); ").arg(mTest.NameByRef())
                                                  .arg( mQueryCreateLecture ? mQueryCreateLecture->getResult() : mLectureId));

    return result;
}

quint32 SqlCreateTest::prepareResultOnError()
{
     return quint32(-1);
}

quint32 SqlCreateTest::prepareResultOnSuccess()
{
    return mLectureId;
}
