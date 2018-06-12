#ifndef TESTUSERANSWERS_H
#define TESTUSERANSWERS_H

#include <QDataStream>
#include <QMultiMap>

class TestUserAnswers
{
public:
    TestUserAnswers();

    quint32 TestId() const;
    QMultiMap<quint32, quint32> Answers() const;

    const quint32& TestIdByRef() const;
    const QMultiMap<quint32, quint32>& AnswersByRef() const;

    void setTestId(const quint32 testId);
    void setAnswers( const QMultiMap<quint32, quint32>& answers);





private:
    quint32 mTestId;
    QMultiMap<quint32, quint32> mAnswers;

public:
    struct Isset {
        bool testId;
        bool answers;
    } __isset;

    friend QDataStream& operator >>(QDataStream& stream, TestUserAnswers& type);
    friend QDataStream& operator <<(QDataStream& stream, const TestUserAnswers& type);
};

#endif // TESTUSERANSWERS_H
