#include "TestQuestionType.hpp"

QDataStream& operator >>(QDataStream& stream, TestQuestionType& type)
{
    quint32 questionType;
    stream >> questionType;
    type = (TestQuestionType) questionType;
    return stream;
}

QDataStream& operator <<(QDataStream& stream, const TestQuestionType& type)
{
    quint32 questionType = (quint32)type;
    stream << questionType;
    return stream;
}
