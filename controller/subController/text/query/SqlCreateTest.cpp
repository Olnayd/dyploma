#include "SqlCreateTest.hpp"
#include "SqlCreateLecture.hpp"

SqlCreateTest::SqlCreateTest(const Test& test, const QString data, const quint32 lectureId)
    : SqlQuery<quint32>(TEXT_STORAGE)
    , mTest(test)
    , mData(data)
    , mLectureId(lectureId)
    , mQueryCreateLecture ( nullptr )
{

}

SqlCreateTest::SqlCreateTest(const Test& test, const QString data, ::std::shared_ptr<SqlCreateLecture> queryCreateLecture)
    : SqlQuery<quint32>(TEXT_STORAGE)
    , mTest(test)
    , mData(data)
    , mLectureId(-1)
    , mQueryCreateLecture(queryCreateLecture)
{

}



QStringList SqlCreateTest::preapareStatement()
{
    QStringList result;
    result.push_back( QString( "INSERT INTO Test(id, name, data) "
                               "VALUES (%1,'%2','%3'); ").arg( mQueryCreateLecture ? mQueryCreateLecture->getResult() : mLectureId  )
                                                     .arg( mTest.NameByRef() )
                                                     .arg( mData ));

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
