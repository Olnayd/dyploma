#ifndef LECTIONPREVIEW_H
#define LECTIONPREVIEW_H

#include <QDataStream>
#include "TestPreview.hpp"


class LectionPreview
{
public:
    LectionPreview();
    LectionPreview(const quint32 id, const QString& name, const QString& description);
    LectionPreview(const quint32 id, const QString& name, const QString& description, const TestPreview& test);


   quint32 Id() const;
   QString Name() const;
   QString Description() const;
   TestPreview Test() const;

   const quint32& IdByRef() const;
   const QString& NameByRef() const;
   const QString& DescriptionByRef() const;
   const TestPreview& TestByRef() const;

   void setId(const quint32 id);
   void setName(const QString& name);
   void setDescription(const QString& description);
   void setTest(const TestPreview& description);

private:
    quint32 mId;
    QString mName;
    QString mDescription;
    TestPreview mTest;

public:
    struct Isset{
        bool id;
        bool name;
        bool description;
        bool test;
    } __isset;

    friend QDataStream& operator >>(QDataStream& stream, LectionPreview& type);
    friend QDataStream& operator <<(QDataStream& stream, const LectionPreview& type);
};




#endif // LECTIONPREVIEW_H
