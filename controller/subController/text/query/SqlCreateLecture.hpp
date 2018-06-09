#ifndef SQLCREATELECTION_HPP
#define SQLCREATELECTION_HPP

#include "database/query/SqlQuery.h"
#include "network/processor/course/types/Lecture.hpp"

class SqlCreateLecture : public SqlQuery<quint32>
{
public:
    SqlCreateLecture(const Lecture& lecture);

private:
    virtual quint32 prepareResultOnError() override final;
    virtual quint32 prepareResultOnSuccess() override final;
    virtual QStringList preapareStatement() override final;

private:
    Lecture mLecture;
};


#endif // SQLCREATELECTION_HPP
