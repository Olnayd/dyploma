#ifndef SQLGETTOPICLIST_HPP
#define SQLGETTOPICLIST_HPP

#include <QVector>
#include "database/query/SqlQuery.h"
#include "network/processor/course/types/CourseTopic.hpp"

class SqlGetTopicList : public SqlQuery<QVector<CourseTopic>>
{
public:
    SqlGetTopicList();

private:
    virtual QVector<CourseTopic> prepareResultOnError() override final;
    virtual QVector<CourseTopic> prepareResultOnSuccess() override final;
    virtual QStringList preapareStatement() override final;
};
#endif // SQLGETTOPICLIST_HPP
