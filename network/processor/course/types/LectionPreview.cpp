#include "LectionPreview.hpp"

LectionPreview::LectionPreview()
    : __isset{false, false, false, false}
{

}

LectionPreview::LectionPreview(const quint32 id, const QString& name, const QString& description)
    : mId(id)
    , mName(name)
    , mDescription(description)
    , __isset{true, true, true, false}
{

}

LectionPreview::LectionPreview(const quint32 id, const QString& name, const QString& description, const TestPreview& test)
    : mId(id)
    , mName(name)
    , mDescription(description)
    , mTest(test)
    , __isset{true, true, true, true}
{
}

quint32 LectionPreview::Id() const
{
    return mId;
}
QString LectionPreview::Name() const
{
    return mName;
}
QString LectionPreview::Description() const
{
    return mDescription;
}
TestPreview LectionPreview::Test() const
{
    return mTest;
}

const quint32& LectionPreview::IdByRef() const
{
    return mId;
}
const QString& LectionPreview::NameByRef() const
{
    return mName;
}
const QString& LectionPreview::DescriptionByRef() const
{
    return mDescription;
}
const TestPreview& LectionPreview::TestByRef() const
{
    return mTest;
}

void LectionPreview::setId(const quint32 id)
{
    __isset.id = true;
    mId = id;
}

void LectionPreview::setName(const QString& name)
{
    __isset.name = true;
    mName = name;
}

void LectionPreview::setDescription(const QString& description)
{
    __isset.description = true;
    mDescription = description;
}
void LectionPreview::setTest(const TestPreview& test)
{
    __isset.test = true;
    mTest = test;
}

QDataStream& operator >>(QDataStream& stream, LectionPreview& type)
{
    stream >> type.mId >> type.mName >> type.mDescription >> type.mTest;
    return stream;
}

QDataStream& operator <<(QDataStream& stream, const LectionPreview& type)
{
    stream << type.mId << type.mName << type.mDescription << type.mTest;
    return stream;
}
