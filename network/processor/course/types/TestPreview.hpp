#ifndef TESTPREVIEW_H
#define TESTPREVIEW_H

#include <QDataStream>

class TestPreview
{
public:
    TestPreview();
    TestPreview(const quint32 id, const QString& name, const QString& description);
    TestPreview(const quint32 id, const QString& name, const QString& description, const qreal evaluation);

    quint32 Id() const;
    QString Name() const;
    QString Description() const;
    qreal Evaluation() const;

    const quint32& IdByRef() const;
    const QString& NameByRef()const;
    const QString& DescriptionByRef() const;
    const qreal& EvaluationByRef() const;

    void setId(const quint32 id);
    void setName(const QString& name);
    void setDescription(const QString& Description);
    void setEvaluation(const qreal);

private:
    quint32 mId;
    QString mName;
    QString mDescription;
    qreal mEvaluation;

public:
    struct Isset
    {
        bool id;
        bool name;
        bool description;
        bool evaluation;
    } __isset;

    friend QDataStream& operator >>(QDataStream& stream, TestPreview& type);
    friend QDataStream& operator <<(QDataStream& stream, const TestPreview& type);
};





#endif // TESTPREVIEW_H
