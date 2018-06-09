#ifndef SQLCOUPLELECTIONTOCOURSE_HPP
#define SQLCOUPLELECTIONTOCOURSE_HPP

#include "controller/subController/text/query/SqlCreateLecture.hpp"
#include <memory>
#include "database/query/SqlQuery.h"

#include "network/processor/course/types/Lecture.hpp"


class SqlCoupleLectureToCourse : public SqlQuery<quint32>
{
public:
    SqlCoupleLectureToCourse(const quint32 courseId, ::std::shared_ptr<SqlCreateLecture> queryCreateLecture );

private:
    virtual quint32 prepareResultOnError() override final;
    virtual quint32 prepareResultOnSuccess() override final;
    virtual QStringList preapareStatement() override final;

private:
    quint32 mCourseId;
    ::std::shared_ptr<SqlCreateLecture> mQueryCreateLection;

};

#endif // SQLCOUPLELECTIONTOCOURSE_HPP
