#include "Test.hpp"

Test::Test()
    : __isset{false, false, false, false}
{

}
Test::Test(const quint32 id, const QString& name)
    : mId(id)
    , mName(name)
    , __isset{true, true, false, false}
{

}

Test::Test(const quint32 id, const QString& name, const qreal evaluation)
    : mId(id)
    , mName(name)
    , mEvaluation(evaluation)
    , __isset{true, true, false, true}
{

}


Test::Test(const quint32 id, const QString& name, const QVector<TestQuestion>& questionList)
    : mId(id)
    , mName(name)
    , mQuestionList(questionList)
    , __isset{true, true, true, false}
{

}

Test::Test(const quint32 id, const QString& name, const QVector<TestQuestion>& questionList, const qreal evaluation)
    : mId(id)
    , mName(name)
    , mQuestionList(questionList)
    , mEvaluation(evaluation)
    , __isset{true, true, true, true}
{
}

quint32 Test::Id() const
{
    return mId;
}
QString Test::Name()const
{
    return mName;
}
QVector<TestQuestion> Test::QuestionList() const
{
    return mQuestionList;
}
qreal Test::Evaluation() const
{
    return mEvaluation;
}

const quint32& Test::IdByRef() const
{
    return mId;
}
const QString& Test::NameByRef() const
{
    return mName;
}
const QVector<TestQuestion>& Test::QuestionListByRef() const
{
    return mQuestionList;
}
const qreal& Test::EvaluationByRef() const
{
    return mEvaluation;
}

void Test::setName(const QString& name)
{
    __isset.name = true;
    mName = name;
}

void Test::setQuestionList(const QVector<TestQuestion>& questionList)
{
    __isset.questionList = true;
    mQuestionList = questionList;
}

void Test::setEvaluation(const qreal evaluation)
{
    __isset.evaluation = true;
    mEvaluation = evaluation;
}

void Test::setId(const quint32 id)
{
    __isset.id = true;
    mId = id;
}


QDataStream& operator >>(QDataStream& stream, Test& type)
{
    stream  >> type.__isset.questionList
            >> type.__isset.evaluation
            >> type.__isset.id
            >> type.__isset.name
            >> type.mId
            >> type.mName
            >> type.mQuestionList
            >> type.mEvaluation;
    return stream;
}

QDataStream& operator <<(QDataStream& stream, const Test& type)
{
    stream  << type.__isset.questionList
            << type.__isset.evaluation
            << type.__isset.id
            << type.__isset.name
            << type.mId
            << type.mName
            << type.mQuestionList
            << type.mEvaluation;
    return stream;
}

