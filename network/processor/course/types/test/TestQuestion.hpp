#ifndef TESTQUESTION_H
#define TESTQUESTION_H

#include <QVector>
#include <QDataStream>
#include "TestAnswer.hpp"
#include "TestQuestionType.hpp"

class TestQuestion
{
public:
    TestQuestion();

    quint32 Id() const;
    QString Text() const;
    TestQuestionType QuestionType() const;
    QVector<TestAnswer> AnswerList() const;

    const quint32& IdByRef() const;
    const QString& TextByRef()const;
    const TestQuestionType& QuestionTypeByRef() const;
    const QVector<TestAnswer>& AnswerListByRef() const;

    void setId( const quint32 id);
    void setText( const QString& text);
    void setQuestionType(const TestQuestionType& questionType);
    void setAnswerList(const QVector<TestAnswer>& answerList);

private:
    quint32 mId;
    QString mText;
    TestQuestionType mQuestionType;
    QVector<TestAnswer> mAnswerList;

public:
    struct Isset {
        bool id;
        bool text;
        bool questionType;
        bool answerList;
    } __isset;

    friend QDataStream& operator >>(QDataStream& stream, TestQuestion& type);
    friend QDataStream& operator <<(QDataStream& stream, const TestQuestion& type);
};

#endif // TESTQUESTION_H
