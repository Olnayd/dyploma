#include "Test.hpp"

Test::Test()
    : __isset{false, false, false, false}
{

}
Test::Test(const quint32 id, const QString& name)
    : mId(id)
    , mName(name)
    , __isset{true, true, false, false}
{

}

Test::Test(const quint32 id, const QString& name, const qreal evaluation)
    : mId(id)
    , mName(name)
    , mEvaluation(evaluation)
    , __isset{true, true, false, true}
{

}


Test::Test(const quint32 id, const QString& name, const QString& data)
    : mId(id)
    , mName(name)
    , mData(data)
    , __isset{true, true, true, false}
{

}

Test::Test(const quint32 id, const QString& name, const QString& data, const qreal evaluation)
    : mId(id)
    , mName(name)
    , mData(data)
    , mEvaluation(evaluation)
    , __isset{true, true, true, true}
{
}

quint32 Test::Id() const
{
    return mId;
}
QString Test::Name()const
{
    return mName;
}
QString Test::Data() const
{
    return mData;
}
qreal Test::Evaluation() const
{
    return mEvaluation;
}

const quint32& Test::IdByRef() const
{
    return mId;
}
const QString& Test::NameByRef() const
{
    return mName;
}
const QString& Test::DataByRef() const
{
    return mData;
}
const qreal& Test::EvaluationByRef() const
{
    return mEvaluation;
}

void Test::setName(const QString& name)
{
    __isset.name = true;
    mName = name;
}

void Test::setData(const QString& data)
{
    __isset.data = true;
    mData = data;
}

void Test::setEvaluation(const qreal evaluation)
{
    __isset.evaluation = true;
    mEvaluation = evaluation;
}

void Test::setId(const quint32 id)
{
    __isset.id = true;
    mId = id;
}


QDataStream& operator >>(QDataStream& stream, Test& type)
{
    stream  >> type.__isset.data
            >> type.__isset.evaluation
            >> type.__isset.id
            >> type.__isset.name
            >> type.mId
            >> type.mName
            >> type.mData
            >> type.mEvaluation;
    return stream;
}

QDataStream& operator <<(QDataStream& stream, const Test& type)
{
    stream  << type.__isset.data
            << type.__isset.evaluation
            << type.__isset.id
            << type.__isset.name
            << type.mId
            << type.mName
            << type.mData
            << type.mEvaluation;
    return stream;
}

