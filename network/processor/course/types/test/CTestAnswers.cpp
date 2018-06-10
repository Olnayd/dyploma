#include "TestAnswer.hpp"

TestAnswer::TestAnswer()
 : mIsRightAnswer(false)
{

}


quint32 TestAnswer::Id() const
{
    return mId;
}

QString TestAnswer::Text() const
{
    return mText;
}
bool TestAnswer::IsRightAnswer() const
{
    return mIsRightAnswer;
}


const quint32& TestAnswer::IdByRef() const
{
    return mId;
}
const QString& TestAnswer::TextByRef() const
{
    return mText;
}
const bool& TestAnswer::IsRightAnswerByRef() const
{
    return mIsRightAnswer;
}



void TestAnswer::setId( const quint32 id)
{
    __isset.id = true;
    mId = id;
}

void TestAnswer::setText( const QString& text)
{
    __isset.text = true;
    mText = text;
}

void TestAnswer::setIsRightAnswer( const bool isRightAnswer )
{
    __isset.isRightAnswer = true;
    mIsRightAnswer = isRightAnswer;
}

QDataStream& operator >>(QDataStream& stream, TestAnswer& type)
{
    stream >> type.__isset.id
           >> type.__isset.text
           >> type.__isset.isRightAnswer
           >> type.mId
           >> type.mText
           >> type.mIsRightAnswer;
    return stream;
}

QDataStream& operator <<(QDataStream& stream, const TestAnswer& type)
{
    stream << type.__isset.id
           << type.__isset.text
           << type.__isset.isRightAnswer
           << type.mId
           << type.mText
           << type.mIsRightAnswer;
    return stream;
}



