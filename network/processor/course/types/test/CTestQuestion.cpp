#include "TestQuestion.hpp"

TestQuestion::TestQuestion()
    : mQuestionType(TestQuestionType::ONE_ANSWER)
    , __isset{false, false, false, false}
{

}

quint32 TestQuestion::Id() const
{
    return mId;
}

QString TestQuestion::Text() const
{
    return mText;
}

TestQuestionType TestQuestion::QuestionType() const
{
    return mQuestionType;
}
QVector<TestAnswer> TestQuestion::AnswerList() const
{
    return mAnswerList;
}

const quint32& TestQuestion::IdByRef() const
{
    return mId;
}
const QString& TestQuestion::TextByRef() const
{
    return mText;
}

const TestQuestionType& TestQuestion::QuestionTypeByRef() const
{
    return mQuestionType;
}
const QVector<TestAnswer>& TestQuestion::AnswerListByRef() const
{
    return mAnswerList;
}

void TestQuestion::setId( const quint32 id)
{
    __isset.id = true;
    mId = id;
}

void TestQuestion::setText( const QString& text)
{
    __isset.text = true;
    mText = text;
}


void TestQuestion::setQuestionType(const TestQuestionType& questionType)
{
    __isset.questionType = true;
    mQuestionType = questionType;
}

void TestQuestion::setAnswerList(const QVector<TestAnswer>& answerList)
{
    __isset.answerList = true;
    mAnswerList = answerList;
}

QDataStream& operator >>(QDataStream& stream, TestQuestion& type)
{
    stream >> type.__isset.id
           >> type.__isset.text
           >> type.__isset.questionType
           >> type.__isset.answerList
           >> type.mId
           >> type.mText
           >> type.mQuestionType
           >> type.mAnswerList;
    return stream;
}

QDataStream& operator <<(QDataStream& stream, const TestQuestion& type)
{
    stream << type.__isset.id
           << type.__isset.text
           << type.__isset.questionType
           << type.__isset.answerList
           << type.mId
           << type.mText
           << type.mQuestionType
           << type.mAnswerList;
    return stream;
}
