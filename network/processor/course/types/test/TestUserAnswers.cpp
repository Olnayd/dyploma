#include "TestUserAnswers.hpp"

TestUserAnswers::TestUserAnswers()
    : __isset{false, false}
{

}

QMultiMap<quint32, quint32> TestUserAnswers::Answers() const
{
    return mAnswers;
}

const QMultiMap<quint32, quint32>& TestUserAnswers::AnswersByRef() const
{
    return mAnswers;
}

void TestUserAnswers::setAnswers( const QMultiMap<quint32, quint32>& answers)
{
    __isset.answers = true;
    mAnswers = answers;
}

quint32 TestUserAnswers::TestId() const
{
    return mTestId;
}

const quint32& TestUserAnswers::TestIdByRef() const
{
    return mTestId;
}

void TestUserAnswers::setTestId(const quint32 testId)
{
    __isset.testId = true;
    mTestId = testId;
}

QDataStream& operator >>(QDataStream& stream, TestUserAnswers& type)
{
    stream  >> type.__isset.answers
            >> type.__isset.testId
            >> type.mAnswers
            >> type.mTestId;
    return stream;
}

QDataStream& operator <<(QDataStream& stream, const TestUserAnswers& type)
{
    stream  << type.__isset.answers
            << type.__isset.testId
            << type.mAnswers
            << type.mTestId;
    return stream;
}

