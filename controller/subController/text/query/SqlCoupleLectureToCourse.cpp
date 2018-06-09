#include "SqlCoupleLectureToCourse.hpp"

SqlCoupleLectureToCourse::SqlCoupleLectureToCourse(const quint32 courseId, ::std::shared_ptr<SqlCreateLecture> queryCreateLecture )
    : SqlQuery<quint32>(TEXT_STORAGE)
    , mCourseId(courseId)
    , mQueryCreateLection(queryCreateLecture)
{

}

QStringList SqlCoupleLectureToCourse::preapareStatement()
{
    QStringList result;
    result.push_back( QString( "INSERT INTO CourseToLecture (id_course, id_lection)"
                               "VALUES (%1, %2);").arg( mCourseId )
                                                  .arg( mQueryCreateLection->getResult() ));
    return result;
}

quint32 SqlCoupleLectureToCourse::prepareResultOnError()
{
     return 0;
}

quint32 SqlCoupleLectureToCourse::prepareResultOnSuccess()
{
    return 1;
}
