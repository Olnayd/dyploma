#ifndef TESTPREVIEW_H
#define TESTPREVIEW_H

#include <QDataStream>

class Test
{
public:
    Test();
    Test(const quint32 id, const QString& name);
    Test(const quint32 id, const QString& name, const qreal evaluation);
    Test(const quint32 id, const QString& name, const QString& data);
    Test(const quint32 id, const QString& name, const QString& data, const qreal evaluation);

    quint32 Id() const;
    QString Name() const;
    QString Data() const;
    qreal Evaluation() const;

    const quint32& IdByRef() const;
    const QString& NameByRef()const;
    const QString& DataByRef() const;
    const qreal& EvaluationByRef() const;

    void setId(const quint32 id);
    void setName(const QString& name);
    void setData(const QString& data);
    void setEvaluation(const qreal);

private:
    quint32 mId;
    QString mName;
    QString mData; //would be changed asap
    qreal mEvaluation;

public:
    struct Isset
    {
        bool id;
        bool name;
        bool data;
        bool evaluation;
    } __isset;

    friend QDataStream& operator >>(QDataStream& stream, Test& type);
    friend QDataStream& operator <<(QDataStream& stream, const Test& type);
};





#endif // TESTPREVIEW_H
