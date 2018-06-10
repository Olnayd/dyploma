#include "Lecture.hpp"

Lecture::Lecture()
    : mId()
    , mName()
    , mData()
    , mIsLectureDone (false)
    , mTest()
    ,  __isset{false, // id
               false, // name
               false, // data
               false, // isLectureDone
               false} // test
{

}
Lecture::Lecture(const quint32 id, const QString& name, const QString& data)
    : mId(id)
    , mName(name)
    , mData(data)
    , mIsLectureDone (false)
    , mTest()
    ,  __isset{true, // id
               true, // name
               true, // data
               false, // isLectureDone
               false} // test
{

}

Lecture::Lecture(const quint32 id, const QString& name)
    : mId(id)
    , mName(name)
    , mData()
    , mIsLectureDone (false)
    , mTest()
    ,  __isset{true,  // id
               true,  // name
               false, // data
               false, // isLectureDone
               false} // test
{

}

Lecture::Lecture(const quint32 id, const QString& name, const bool isLectureDone)
    : mId(id)
    , mName(name)
    , mData()
    , mIsLectureDone (isLectureDone)
    , mTest()
    ,  __isset{true,  // id
               true,  // name
               false, // data
               true,  // isLectureDone
               false} // test
{

}

Lecture::Lecture(const quint32 id, const QString& name, const QString& data, const bool isLectureDone)
    : mId(id)
    , mName(name)
    , mData(data)
    , mIsLectureDone (isLectureDone)
    , mTest()
    , __isset{true,  // id
              true,  // name
              true,  // data
              true,  // isLectureDone
              false} // test
{
}

Lecture::Lecture(const quint32 id, const QString& name, const bool isLectureDone, const ::Test& test)
    : mId(id)
    , mName(name)
    , mData()
    , mIsLectureDone(isLectureDone)
    , mTest(test)
    , __isset{true,  // id
              true,  // name
              false, // data
              true,  // isLectureDone
              true}  // test
{
}



Lecture::Lecture(const quint32 id, const QString& name, const QString& data, const bool isLectureDone, const ::Test& test)
    : mId(id)
    , mName(name)
    , mData(data)
    , mIsLectureDone(isLectureDone)
    , mTest(test)
    , __isset{true, // id
              true, // name
              true, // data
              true, // isLectureDone
              true} // test
{

}




quint32 Lecture::Id() const
{
    return mId;
}
QString Lecture::Name() const
{
    return mName;
}

QString Lecture::Data() const
{
    return mData;
}
bool Lecture::IsLectureDone() const
{
    return mIsLectureDone;
}
Test Lecture::Test() const
{
    return mTest;
}

const quint32& Lecture::IdByRef() const
{
    return mId;
}
const QString& Lecture::NameByRef() const
{
    return mName;
}
const QString& Lecture::DataByRef() const
{
    return mData;
}
const bool& Lecture::IsLectureDoneByRef() const
{
    return mIsLectureDone;
}
const Test& Lecture::TestByRef() const
{
    return mTest;
}



void Lecture::setId(const quint32 id)
{
    __isset.id = true;
    mId = id;
}

void Lecture::setName(const QString& name)
{
    __isset.name = true;
    mName = name;
}

void Lecture::setData(const QString& data)
{
    __isset.data = true;
    mData = data;
}

void Lecture::setIsLectureDone(const bool isLectureDone)
{
    __isset.isLectureDone = true;
    mIsLectureDone = isLectureDone;
}

void Lecture::setTest(const ::Test& test)
{
    __isset.test = true;
    mTest = test;
}

QDataStream& operator >>(QDataStream& stream, Lecture& type)
{
    stream >> type.__isset.id
           >> type.__isset.name
           >> type.__isset.data
           >> type.__isset.isLectureDone
           >> type.__isset.test
           >> type.mId
           >> type.mName
           >> type.mData
           >> type.mIsLectureDone
           >> type.mTest;
    return stream;
}

QDataStream& operator <<(QDataStream& stream, const Lecture& type)
{
    stream << type.__isset.id
           << type.__isset.name
           << type.__isset.data
           << type.__isset.isLectureDone
           << type.__isset.test
           << type.mId
           << type.mName
           << type.mData
           << type.mIsLectureDone
           << type.mTest;
    return stream;
}
