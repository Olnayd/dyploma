#ifndef TESTANSWERS_H
#define TESTANSWERS_H

#include <QDataStream>

class TestAnswer
{
public:
    TestAnswer();

    quint32 Id() const;
    QString Text() const;
    bool IsRightAnswer() const;

    const quint32& IdByRef() const;
    const QString& TextByRef()const;
    const bool& IsRightAnswerByRef() const;

    void setId( const quint32 id);
    void setText( const QString& text);
    void setIsRightAnswer( const bool isRightAnswer);

private:
    quint32 mId;
    QString mText;
    bool mIsRightAnswer;
public:
    struct Isset
    {
        bool id;
        bool text;
        bool isRightAnswer;
    } __isset;

    friend QDataStream& operator >>(QDataStream& stream, TestAnswer& type);
    friend QDataStream& operator <<(QDataStream& stream, const TestAnswer& type);
};

#endif // TESTANSWERS_H
