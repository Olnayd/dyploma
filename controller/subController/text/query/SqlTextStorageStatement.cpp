#include "SqlTextStorageStatement.hpp"

#include <QVariant>
#include <QDebug>
#include <QString>
#include <database/CSqlConstants.h>

SqlTextStorageStatement::SqlTextStorageStatement(EStorage storageType)
    : SqlQuery<void>(storageType)
{

}

QStringList SqlTextStorageStatement::preapareStatement()
{
    QStringList result;
    result.reserve(30);
    result.push_back( QString( "DROP TABLE IF EXISTS Version;" ) );
    result.push_back( QString( "DROP TABLE IF EXISTS User;" ) );
    result.push_back( QString( "DROP TABLE IF EXISTS Topic;" ) );
    result.push_back( QString( "DROP TABLE IF EXISTS Course;" ) );
    result.push_back( QString( "DROP TABLE IF EXISTS Lecture;" ) );
    result.push_back( QString( "DROP TABLE IF EXISTS Test;" ) );
    result.push_back( QString( "DROP TABLE IF EXISTS Rating;" ) );
    result.push_back( QString( "DROP TABLE IF EXISTS CourseRating;" ) );
    result.push_back( QString( "DROP TABLE IF EXISTS CourseToLecture;" ) );
    result.push_back( QString( "DROP TABLE IF EXISTS TopicToCourse;" ) );
    result.push_back( QString( "DROP TABLE IF EXISTS CourseToListener;" ) );


    result.push_back( QString( "CREATE TABLE IF NOT EXISTS Version( \
                                major INTEGER,        \
                                minor INTEGER);" ) );

    result.push_back( QString( "CREATE TABLE IF NOT EXISTS User(                     \
                               id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,        \
                               login TEXT NOT NULL UNIQUE,                           \
                               password TEXT NOT NULL,                               \
                               name TEXT NOT NULL,                                   \
                               last_name TEXT NOT NULL,                              \
                               type NUMERIC(0,1) NOT NULL,                           \
                               phone_number TEXT,                                    \
                               email TEXT NOT NULL,                                  \
                               address TEXT                                          \
                               );"  ) );

    result.push_back( QString( "CREATE TABLE IF NOT EXISTS Topic(                    \
                               id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,        \
                               name TEXT                                             \
                               );" )
            );

     result.push_back( QString( "CREATE TABLE IF NOT EXISTS Course(                  \
                                 id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,      \
                                 name TEXT,                                          \
                                 description TEXT                                    \
                                 );" )
             );

     result.push_back( QString( "CREATE TABLE IF NOT EXISTS Lecture(                 \
                                 id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,      \
                                 name TEXT,                                          \
                                 data TEXT                                           \
                                 );" )
             );
     result.push_back( QString( "CREATE TABLE IF NOT EXISTS Test(                    \
                                id_lecture INTEGER NOT NULL,                         \
                                name TEXT,                                           \
                                data TEXT,                                           \
                                FOREIGN KEY (id_lecture) REFERENCES Lecture(id),     \
                                PRIMARY KEY (id_lecture)                             \
                                );" )
             );
     result.push_back( QString( "CREATE TABLE IF NOT EXISTS Rating(                  \
                                id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,       \
                                name NUMERIC(1,5)                                    \
                                );" )
             );


     result.push_back( QString( "CREATE TABLE IF NOT EXISTS TopicToCourse(           \
                                id_topic INTEGER NOT NULL,                           \
                                id_course INTEGER NOT NULL,                          \
                                FOREIGN KEY (id_topic) REFERENCES Topic(id),         \
                                FOREIGN KEY (id_course) REFERENCES Course(id),       \
                                PRIMARY KEY (id_topic, id_course)                    \
                                );" )
             );

     result.push_back( QString( "CREATE TABLE IF NOT EXISTS CourseToListener(        \
                                id_user INTEGER NOT NULL,                            \
                                id_course INTEGER NOT NULL,                          \
                                FOREIGN KEY (id_user) REFERENCES User(id),           \
                                FOREIGN KEY (id_course) REFERENCES Course(id),       \
                                PRIMARY KEY (id_user, id_course)                     \
                                );" )
             );

     result.push_back( QString( "CREATE TABLE IF NOT EXISTS CourseToCreator(         \
                                id_user INTEGER NOT NULL,                            \
                                id_course INTEGER NOT NULL,                          \
                                FOREIGN KEY (id_user) REFERENCES User(id),           \
                                FOREIGN KEY (id_course) REFERENCES Course(id),       \
                                PRIMARY KEY (id_user, id_course)                     \
                                );" )
             );

     result.push_back( QString( "CREATE TABLE IF NOT EXISTS CourseRating(            \
                                id_user INTEGER NOT NULL,                            \
                                id_course INTEGER NOT NULL,                          \
                                id_rating_range INTEGER NOT NULL,                    \
                                FOREIGN KEY (id_user) REFERENCES User(id),           \
                                FOREIGN KEY (id_course) REFERENCES Course(id),       \
                                FOREIGN KEY (id_rating_range) REFERENCES Rating(id), \
                                PRIMARY KEY (id_user, id_course)                     \
                                );" )
             );

     result.push_back( QString( "CREATE TABLE IF NOT EXISTS CourseToLecture(         \
                                id_course INTEGER NOT NULL,                          \
                                id_lecture INTEGER NOT NULL,                         \
                                position INTEGER NOT NULL,                           \
                                FOREIGN KEY (id_course) REFERENCES Course(id),       \
                                FOREIGN KEY (id_lecture) REFERENCES Lecture(id),     \
                                PRIMARY KEY (id_course, id_lecture)                  \
                                );" )
             );

     result.push_back( QString( "INSERT INTO Version  \
                                 VALUES (%1, %2);").arg( database::constant::TextStorageVersion.major)
                                                   .arg( database::constant::TextStorageVersion.minor) );
     result.push_back( QString( "INSERT INTO Topic (name)  \
                                 VALUES ('%1'), ('%2'), ('%3');").arg( "C/C++" )
                                                                 .arg( "Java" )
                                                                 .arg( "SQL" ));


    return result;
}

void SqlTextStorageStatement::prepareResultOnError()
{
    //dummy implementation
}
void SqlTextStorageStatement::prepareResultOnSuccess()
{
    //dummy implementation
}

