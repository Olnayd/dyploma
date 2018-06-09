#ifndef SQLGETLECTUREPREVIEWLIST_HPP
#define SQLGETLECTUREPREVIEWLIST_HPP

#include <QVector>
#include "database/query/SqlQuery.h"
#include "network/processor/course/types/Lecture.hpp"


class SqlGetLecturePreviewList : public SqlQuery<QVector<Lecture>>
{
public:
    SqlGetLecturePreviewList(const quint32 courseId);

private:
    virtual QVector<Lecture> prepareResultOnError() override final;
    virtual QVector<Lecture> prepareResultOnSuccess() override final;
    virtual QStringList preapareStatement() override final;

private:
    quint32 mCourseId;
};

#endif // SQLGETLECTUREPREVIEWLIST_HPP
