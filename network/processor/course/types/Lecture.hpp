#ifndef LECTIONPREVIEW_H
#define LECTIONPREVIEW_H

#include <QDataStream>
#include "Test.hpp"

class Lecture
{
public:
    Lecture();
    Lecture(const quint32 id, const QString& name);
    Lecture(const quint32 id, const QString& name, const QString& data);
    Lecture(const quint32 id, const QString& name, const bool isLectureDone);
    Lecture(const quint32 id, const QString& name, const bool isLectureDone, const ::Test& test);
    Lecture(const quint32 id, const QString& name, const QString& data, const bool isLectureDone);
    Lecture(const quint32 id, const QString& name, const QString& data, const bool isLectureDone, const ::Test& test);

    quint32 Id() const;
    QString Name() const;
    QString Data() const;
    bool IsLectureDone() const;
    ::Test Test() const;

    const quint32& IdByRef() const;
    const QString& NameByRef() const;
    const QString& DataByRef() const;
    const bool& IsLectureDoneByRef() const;
    const ::Test& TestByRef() const;

    void setId(const quint32 id);
    void setName(const QString& name);
    void setData(const QString& data);
    void setIsLectureDone(const bool isLectureDone);
    void setTest(const ::Test& test);

private:
    quint32 mId;
    QString mName;
    QString mData;
    bool mIsLectureDone;
    ::Test mTest;

public:
    struct Isset{
        bool id;
        bool name;
        bool data;
        bool isLectureDone;
        bool test;
    } __isset;

    friend QDataStream& operator >>(QDataStream& stream, Lecture& type);
    friend QDataStream& operator <<(QDataStream& stream, const Lecture& type);
};




#endif // LECTIONPREVIEW_H
