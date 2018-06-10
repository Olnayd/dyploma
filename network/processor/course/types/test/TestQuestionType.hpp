#ifndef TESTQUESTIONTYPE_H
#define TESTQUESTIONTYPE_H

#include <QDataStream>

enum TestQuestionType
{
    ONE_ANSWER,
    ONE_OR_MORE_ANSWERS
};

QDataStream& operator >>(QDataStream& stream, TestQuestionType& type);
QDataStream& operator <<(QDataStream& stream, const TestQuestionType& type);

#endif // TESTQUESTIONTYPE_H
