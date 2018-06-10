#include "SqlGetLecture.hpp"


SqlGetLecture::SqlGetLecture(const quint32 lectureId)
    : SqlQuery<Lecture>(TEXT_STORAGE)
    , mLectureId(lectureId)
{

}

QStringList SqlGetLecture::preapareStatement()
{
    QStringList result;
    result.push_back( QString( " SELECT Lecture.id, Lecture.name, Lecture.data,"
                               " CASE WHEN Test.id IS NULL THEN 0 ELSE 1 END AS IsTestExist, "
                               " Test.id, Test.name, Test.data"
                               " FROM Lecture "
                               " LEFT JOIN Test on Lecture.id  = Test.id "
                               " WHERE Lecture.id = %1 " ).arg(mLectureId));
    return result;
}

Lecture SqlGetLecture::prepareResultOnError()
{
    return Lecture();
}

Lecture SqlGetLecture::prepareResultOnSuccess()
{
    while (next())
    {
        quint32 lectureId   = value(0).toInt();
        QString lectureName = value(1).toString();
        QString lectureData = value(2).toString();
        bool isTestExist = (bool)value(3).toInt();

        Lecture lecture(lectureId, lectureName, lectureData);

        if (isTestExist)
        {
            quint32 testId = value(4).toInt();
            QString testName = value(5).toString();
            testData = value(6).toString();
            Test test(testId, testName);
            lecture.setTest(test);
        }

        return lecture;
    }
    return prepareResultOnError();
}
