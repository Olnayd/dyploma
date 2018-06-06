#ifndef SQLCREATELECTION_H
#define SQLCREATELECTION_H

#include "database/query/SqlQuery.h"
#include "network/processor/course/types/LectionInformation.hpp"

class SqlCreateLection : public SqlQuery<quint32>
{
public:
    SqlCreateLection(const LectionInformation& lectionInformation, const quint32 courseId);

private:
    virtual quint32 prepareResultOnError() override final;
    virtual quint32 prepareResultOnSuccess() override final;
    virtual QStringList preapareStatement() override final;

private:
    LectionInformation mLectionInformation;
    quint32 mCourseId;
};


#endif // SQLCREATELECTION_H
