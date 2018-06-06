#include "TestPreview.hpp"

TestPreview::TestPreview()
    : __isset{false, false, false, false}
{

}

TestPreview::TestPreview(const quint32 id, const QString& name, const QString& description)
    : mId(id)
    , mName(name)
    , mDescription(description)
    , __isset{true, true, true, false}
{

}

TestPreview::TestPreview(const quint32 id, const QString& name, const QString& description, const qreal evaluation)
    : mId(id)
    , mName(name)
    , mDescription(description)
    , mEvaluation(evaluation)
    , __isset{true, true, true, true}
{
}

quint32 TestPreview::Id() const
{
    return mId;
}
QString TestPreview::Name()const
{
    return mName;
}
QString TestPreview::Description() const
{
    return mDescription;
}
qreal TestPreview::Evaluation() const
{
    return mEvaluation;
}

const quint32& TestPreview::IdByRef() const
{
    return mId;
}
const QString& TestPreview::NameByRef() const
{
    return mName;
}
const QString& TestPreview::DescriptionByRef() const
{
    return mDescription;
}
const qreal& TestPreview::EvaluationByRef() const
{
    return mEvaluation;
}

void TestPreview::setName(const QString& name)
{
    __isset.name = true;
    mName = name;
}

void TestPreview::setDescription(const QString& description)
{
    __isset.description = true;
    mDescription = description;
}

void TestPreview::setEvaluation(const qreal evaluation)
{
    __isset.evaluation = true;
    mEvaluation = evaluation;
}

void TestPreview::setId(const quint32 id)
{
    __isset.id = true;
    mId = id;
}


QDataStream& operator >>(QDataStream& stream, TestPreview& type)
{
    stream >> type.mId >> type.mName >> type.mDescription >> type.mEvaluation;
    return stream;
}

QDataStream& operator <<(QDataStream& stream, const TestPreview& type)
{
    stream << type.mId << type.mName << type.mDescription << type.mEvaluation;
    return stream;
}

