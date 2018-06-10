#ifndef TESTPREVIEW_H
#define TESTPREVIEW_H

#include <QDataStream>
#include "TestQuestion.hpp"

class Test
{
public:
    Test();
    Test(const quint32 id, const QString& name);
    Test(const quint32 id, const QString& name, const qreal evaluation);
    Test(const quint32 id, const QString& name, const QVector<TestQuestion>& questionList);
    Test(const quint32 id, const QString& name, const QVector<TestQuestion>& questionList, const qreal evaluation);

    quint32 Id() const;
    QString Name() const;
    QVector<TestQuestion> QuestionList() const;
    qreal Evaluation() const;

    const quint32& IdByRef() const;
    const QString& NameByRef()const;
    const QVector<TestQuestion>& QuestionListByRef() const;
    const qreal& EvaluationByRef() const;

    void setId(const quint32 id);
    void setName(const QString& name);
    void setQuestionList(const QVector<TestQuestion>& questionList);
    void setEvaluation(const qreal);

private:
    quint32 mId;
    QString mName;
    QVector<TestQuestion> mQuestionList; //would be changed asap
    qreal mEvaluation;

public:
    struct Isset
    {
        bool id;
        bool name;
        bool questionList;
        bool evaluation;
    } __isset;

    friend QDataStream& operator >>(QDataStream& stream, Test& type);
    friend QDataStream& operator <<(QDataStream& stream, const Test& type);
};





#endif // TESTPREVIEW_H
