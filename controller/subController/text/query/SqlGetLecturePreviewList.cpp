#include "SqlGetLecturePreviewList.hpp"


SqlGetLecturePreviewList::SqlGetLecturePreviewList(const quint32 courseId)
    : SqlQuery<QVector<Lecture>>(TEXT_STORAGE)
    , mCourseId(courseId)
{

}

QStringList SqlGetLecturePreviewList::preapareStatement()
{
    QStringList result;
    result.push_back( QString( " SELECT Lecture.id, Lecture.name, "
                               " CASE WHEN Test.id IS NULL THEN 0 ELSE 1 END AS IsTestExist,  "
                               "  Test.id, Test.name "
                               " FROM Lecture "
                               " LEFT JOIN Test on Test.id = Lecture.id "
                               " LEFT JOIN CourseToLecture on CourseToLecture.id_lecture = Lecture.id "
                               " where CourseToLecture.id_course = %1" ).arg(mCourseId));





    return result;
}

QVector<Lecture> SqlGetLecturePreviewList::prepareResultOnError()
{
    return QVector<Lecture>();
}

QVector<Lecture> SqlGetLecturePreviewList::prepareResultOnSuccess()
{
    QVector<Lecture> result;
    while (next())
    {
        quint32 lectureId = value(0).toInt();
        QString lectureName = value(1).toString();
        bool isTestExist = (bool)value(2).toInt();

        Lecture lecture(lectureId, lectureName);

        if (isTestExist)
        {
            quint32 testId = value(3).toInt();
            QString testName = value(4).toString();
            Test test(testId, testName);
            lecture.setTest(test);
        }

        result.push_back(lecture);
    }
    return result;
}
