#ifndef SQLGETLECTION_H
#define SQLGETLECTION_H

#include "database/query/SqlQuery.h"
#include "network/processor/course/types/lecture/Lecture.hpp"


class SqlGetLecture : public SqlQuery<Lecture>
{
public:
    SqlGetLecture(const quint32 lectureId);

private:
    virtual Lecture prepareResultOnError() override final;
    virtual Lecture prepareResultOnSuccess() override final;
    virtual QStringList preapareStatement() override final;

private:
    quint32 mLectureId;
public:
    QString testData;
};


#endif // SQLGETLECTION_H
