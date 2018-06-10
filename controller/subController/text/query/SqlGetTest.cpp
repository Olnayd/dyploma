#include "SqlGetTest.hpp"


SqlGetTest::SqlGetTest(const quint32 lectureId)
    : SqlQuery<Test>(TEXT_STORAGE)
    , mLectureId(lectureId)
{

}

QStringList SqlGetTest::preapareStatement()
{
    QStringList result;
    result.push_back( QString( " SELECT Test.id, Test.name, Test.data "
                               " FROM Test "
                               " WHERE Test.id = %1 " ).arg(mLectureId));
    return result;
}

Test SqlGetTest::prepareResultOnError()
{
    return Test();
}

Test SqlGetTest::prepareResultOnSuccess()
{
    while (next())
    {
        quint32 testId   = value(0).toInt();
        QString testName = value(1).toString();
        QString testData = value(2).toString();

        data = testData;
        Test test(testId, testName);
        return test;
    }
    return prepareResultOnError();
}
