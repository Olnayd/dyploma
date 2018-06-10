#include "CTextStorageSubCtrl.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include "database/CSqlConstants.h"
#include "database/query/SqlGetSchemaVersion.h"
#include "query/SqlTextStorageStatement.hpp"
#include "query/SqlGetTopicList.hpp"
#include "query/SqlGetAllCourses.hpp"
#include "query/SqlGetTopicListForCourse.hpp"
#include "query/SqlGetCourseListWhereUserIsCreator.hpp"
#include "query/SqlGetCourseListWhereUserIsListener.hpp"
#include "query/SqlSubscribeOnCourse.h"
#include "query/SqlCreateCourse.hpp"
#include "query/SqlCreateLecture.hpp"
#include "query/SqlCheckIsUserCreatorByCourseId.hpp"
#include "query/SqlCheckIsUserListenerByCourseId.hpp"
#include "query/SqlCoupleLectureToCourse.hpp"
#include "query/SqlCreateTest.hpp"
#include "query/SqlGetLecture.hpp"
#include "query/SqlGetLecturePreviewList.hpp"
#include "query/SqlCheckIsLectureIsDone.hpp"
#include "query/SqlCheckIsUserCreatorByLectureId.hpp"
#include "query/SqlCheckIsUserListenerByLectureId.hpp"
#include "query/SqlGetTest.hpp"



CTextStorageSubCtrl::CTextStorageSubCtrl(std::shared_ptr<CSqlSubCtrl> sqlController)
     : mSqlController( sqlController )
{

}

bool CTextStorageSubCtrl::init()
{
    SqlGetSchemaVersion stmt (EStorage::TEXT_STORAGE) ;
    mSqlController->executeQuery(stmt);
    common::version dbVersion = stmt.getResult();

    if ( database::constant::TextStorageVersion != dbVersion)
    {
        qDebug()<< "[" << getName() << "]"
                << "different database versions. Expected"
                << database::constant::TextStorageVersion.major
                << ":"
                << database::constant::TextStorageVersion.minor
                << "but"
                << dbVersion.major
                << ":"
                << dbVersion.minor
                << "is come.";

        SqlTextStorageStatement stmtInitImage (EStorage::TEXT_STORAGE);
        if ( !mSqlController->executeQuery(stmtInitImage) )
        {
            qDebug()<< "[" << getName() << "]" << "re-creation of DB failed";
            return false;
        }
    }
    return true;
}

const char* CTextStorageSubCtrl::getName()
{
    return "CTextStorageSubCtrl";
}

bool CTextStorageSubCtrl::prepareShutdown()
{
    return true;
}


void CTextStorageSubCtrl::getTopicList(const CResponseContext& responseContext, ICourseResponseHandle& reponseHandle)
{
    SqlGetTopicList query;
    if(mSqlController->executeQuery(query))
    {
        reponseHandle.response_getTopicList(query.getResult(), responseContext);
    }
    else
        reponseHandle.response_error(Error_WTF, responseContext);
}

void CTextStorageSubCtrl::getCourseListByFilter( const qint32 clientdatabaseid, const CourseListWorkingType workType, const CourseListFilter& filter, const CResponseContext& responseContext, ICourseResponseHandle& reponseHandle)
{
    SqlQuery<QVector<Course>>* queryFetchAllCourses;
    switch(workType)
    {
    case CourseListWorkingType::ALL: queryFetchAllCourses = new SqlGetAllCourses(filter);break;
    case CourseListWorkingType::USER_IS_CREATOR: queryFetchAllCourses = new SqlGetCourseListWhereUserIsCreator(filter, clientdatabaseid); break;
    case CourseListWorkingType::USER_IS_LISTENER: queryFetchAllCourses = new SqlGetCourseListWhereUserIsListener(filter, clientdatabaseid); break;
    }

    if(mSqlController->executeQuery(*queryFetchAllCourses))
    {
        QVector<Course> courseInfoList = queryFetchAllCourses->getResult();
        for(Course& course : courseInfoList)
        {
            SqlGetTopicListForCourse queryTopicListForCourse(course.id);
            if(mSqlController->executeQuery(queryTopicListForCourse))
            {
                course.topicList = queryTopicListForCourse.getResult();
            }
        }
        reponseHandle.response_getCourseList(courseInfoList, responseContext);
    }
    else
        reponseHandle.response_error(Error_WTF, responseContext);
}

void CTextStorageSubCtrl::subscribeOnCourse( const qint32 clientdatabaseid,const quint32 courseid, const CResponseContext& responseContext, ICourseResponseHandle& reponseHandle)
{
    SqlSubscribeOnCourse query(courseid, clientdatabaseid);
    if(mSqlController->executeQuery(query))
    {
        reponseHandle.response_subscribeOnCourse(query.getResult(), responseContext);
    }
    else
        reponseHandle.response_error(Error_WTF, responseContext);
}

void CTextStorageSubCtrl::createCourse( const qint32 clientdatabaseid, const Course& courseInfo, const CResponseContext& responseContext, ICourseResponseHandle& reponseHandle)
{
    SqlCreateCourse query(courseInfo, clientdatabaseid);
    if(mSqlController->executeQuery(query))
    {
        reponseHandle.response_createCourse(query.getResult(), responseContext);
    }
    else
        reponseHandle.response_error(Error_WTF, responseContext);

}

void CTextStorageSubCtrl::getTest(const qint32 clientDatabaseId, const ClientType clientType, const quint32 lectureId, const CResponseContext& responseContext, ICourseResponseHandle& reponseHandle)
{
    switch (clientType)
    {
    case ClientType::Student:
    {
        SqlCheckIsUserListenerByLectureId queryIsUserListener(clientDatabaseId, lectureId);
        if(mSqlController->executeQuery(queryIsUserListener) && queryIsUserListener.getResult())
        {
            SqlGetTest querySqlGetTest(lectureId);
            if(mSqlController->executeQuery(querySqlGetTest))
            {
                Test result = querySqlGetTest.getResult();
                QString testData = querySqlGetTest.data;
                QVector<TestQuestion> questionList = getTestQuestionFromJson(testData, true);
                if (!questionList.isEmpty()) result.setQuestionList(questionList);

                reponseHandle.response_getTest(result, responseContext);
            }
            else
                reponseHandle.response_error(Error_WTF, responseContext);
        }
        else
            reponseHandle.response_error(Error_WTF, responseContext);

    } break;

    case ClientType::Teacher:
    {
        SqlCheckIsUserCreatorByLectureId queryIsUserListener(clientDatabaseId, lectureId);
        if(mSqlController->executeQuery(queryIsUserListener) && queryIsUserListener.getResult())
        {
            SqlGetTest querySqlGetTest(lectureId);
            if(mSqlController->executeQuery(querySqlGetTest))
            {
                Test result = querySqlGetTest.getResult();
                QString testData = querySqlGetTest.data;
                QVector<TestQuestion> questionList = getTestQuestionFromJson(testData, false);
                if (!questionList.isEmpty()) result.setQuestionList(questionList);

                reponseHandle.response_getTest(result, responseContext);
            }
            else
                reponseHandle.response_error(Error_WTF, responseContext);
        }
        else
            reponseHandle.response_error(Error_WTF, responseContext);
    } break;

    default:
        reponseHandle.response_error(Error_WTF, responseContext);
    }
}

void CTextStorageSubCtrl::createTest(const qint32 clientDatabaseId, const quint32 lectureId, const Test& test, const CResponseContext& responseContext, ICourseResponseHandle& reponseHandle)
{
    SqlCheckIsUserCreatorByLectureId queryIsUserCreator(clientDatabaseId, lectureId);
    if(mSqlController->executeQuery(queryIsUserCreator) && queryIsUserCreator.getResult())
    {
        QString testData = getTestQuestionAsJson(test);
        SqlCreateTest querySqlCreateTest(test, testData, lectureId);
        if(mSqlController->executeQuery(querySqlCreateTest))
        {
            reponseHandle.response_createTest(querySqlCreateTest.getResult(), responseContext);
        }
        else
            reponseHandle.response_error(Error_WTF, responseContext);
    }
    else
        reponseHandle.response_error(Error_WTF, responseContext);
}

void CTextStorageSubCtrl::createLecture(const qint32 clientDatabaseId, const quint32 courseId, const Lecture& lecture, const CResponseContext& responseContext, ICourseResponseHandle& reponseHandle)
{
    SqlCheckIsUserCreatorByCourseId queryIsUserCreator(clientDatabaseId, courseId);
    if(mSqlController->executeQuery(queryIsUserCreator) && queryIsUserCreator.getResult())
    {
        std::shared_ptr<SqlCreateLecture>         queryCreateLecture         = ::std::make_shared<SqlCreateLecture>(lecture);
        std::shared_ptr<SqlCoupleLectureToCourse> queryCoupleLectureToCourse = ::std::make_shared<SqlCoupleLectureToCourse>(courseId, queryCreateLecture);
        std::shared_ptr<SqlCreateTest>            queryCreateTest;

        QVector<std::shared_ptr<SqlQuery<quint32>>> toExecute;
        toExecute.push_back(queryCreateLecture);
        toExecute.push_back(queryCoupleLectureToCourse);

        if(lecture.__isset.test)
        {
            QString testData = getTestQuestionAsJson(lecture.Test());
            queryCreateTest = ::std::make_shared<SqlCreateTest>(lecture.Test(), testData, queryCreateLecture);
            toExecute.push_back(queryCreateTest);
        }

        if(mSqlController->executeQueryList(toExecute))
        {
            bool isAllOkey = queryCreateLecture->getResult();
            if(isAllOkey)isAllOkey = (bool)queryCoupleLectureToCourse->getResult();
            if(lecture.__isset.test && isAllOkey)isAllOkey = (bool)queryCreateTest->getResult();

            if(isAllOkey)
                reponseHandle.response_createLecture(true,responseContext);
            else
                reponseHandle.response_createLecture(false,responseContext);
        }
        else
            reponseHandle.response_error(Error_WTF, responseContext);
    }
    else
        reponseHandle.response_error(Error_WTF, responseContext);
}

void CTextStorageSubCtrl::getLecture( const qint32 clientDatabaseId, const ClientType clientType, const quint32 lectureId, const CResponseContext& responseContext, ICourseResponseHandle& reponseHandle)
{

    switch (clientType)
    {
    case ClientType::Student:
    {
        SqlCheckIsUserListenerByLectureId queryIsUserListener(clientDatabaseId, lectureId);
        if(mSqlController->executeQuery(queryIsUserListener) && queryIsUserListener.getResult())
        {
            SqlGetLecture queryGetLecture(lectureId);
            if(mSqlController->executeQuery(queryGetLecture))
            {
                SqlCheckIsLectureIsDone queryCheckIsLectureDone(clientDatabaseId, lectureId);
                if(mSqlController->executeQuery(queryCheckIsLectureDone))
                {
                    Lecture result = queryGetLecture.getResult();
                    result.setIsLectureDone(queryCheckIsLectureDone.getResult());

                    if(result.__isset.test)
                    {
                        Test toConvert = result.Test();
                        QString testData = queryGetLecture.testData;
                        QVector<TestQuestion> questionList = getTestQuestionFromJson(testData, true);
                        if (false == questionList.empty())
                        {
                            toConvert.setQuestionList(questionList);
                            result.setTest(toConvert);
                        }
                    }
                    reponseHandle.response_getLecture(result, responseContext);
                }
                else
                    reponseHandle.response_error(Error_WTF, responseContext);
            }
            else
                reponseHandle.response_error(Error_WTF, responseContext);
        }
        else
            reponseHandle.response_error(Error_WTF, responseContext);

    } break;

    case ClientType::Teacher:
    {
        SqlCheckIsUserCreatorByLectureId queryIsUserListener(clientDatabaseId, lectureId);
        if(mSqlController->executeQuery(queryIsUserListener) && queryIsUserListener.getResult())
        {
            SqlGetLecture queryGetLecture(lectureId);
            if(mSqlController->executeQuery(queryGetLecture))
            {
                SqlCheckIsLectureIsDone queryCheckIsLectureDone(clientDatabaseId, lectureId);
                if(mSqlController->executeQuery(queryCheckIsLectureDone))
                {
                    Lecture result = queryGetLecture.getResult();
                    result.setIsLectureDone(queryCheckIsLectureDone.getResult());

                    if(result.__isset.test)
                    {
                        Test toConvert = result.Test();
                        QString testData = queryGetLecture.testData;
                        QVector<TestQuestion> questionList = getTestQuestionFromJson(testData, false);
                        if (false == questionList.empty())
                        {
                            toConvert.setQuestionList(questionList);
                            result.setTest(toConvert);
                        }
                    }
                    reponseHandle.response_getLecture(result, responseContext);
                }
                else
                    reponseHandle.response_error(Error_WTF, responseContext);
            }
            else
                reponseHandle.response_error(Error_WTF, responseContext);
        }
        else
            reponseHandle.response_error(Error_WTF, responseContext);
    } break;

    default:
        reponseHandle.response_error(Error_WTF, responseContext);
    }
}

void CTextStorageSubCtrl::getLecturePreviewList( const qint32 clientDatabaseId, const ClientType clientType, const quint32 courseid, const CResponseContext& responseContext, ICourseResponseHandle& reponseHandle)
{
    switch (clientType)
    {
    case ClientType::Student:
    {
        SqlCheckIsUserListenerByCourseId queryIsUserListener(clientDatabaseId, courseid);
        if(mSqlController->executeQuery(queryIsUserListener) && queryIsUserListener.getResult())
        {
            SqlGetLecturePreviewList queryGetLecturePreviewList(courseid);
            if(mSqlController->executeQuery(queryGetLecturePreviewList))
            {
               bool isErrorOccurs;
                QVector<Lecture> result = queryGetLecturePreviewList.getResult();

                for (Lecture& lecture : result)
                {
                    SqlCheckIsLectureIsDone queryCheckIsLectureDone(clientDatabaseId, lecture.IdByRef());
                    if(!mSqlController->executeQuery(queryCheckIsLectureDone))
                    {isErrorOccurs =true; break;}
                    lecture.setIsLectureDone(queryCheckIsLectureDone.getResult());
                }

                if(isErrorOccurs)
                    reponseHandle.response_error(Error_WTF, responseContext);
                else
                    reponseHandle.response_getLecturePreviewList(result, responseContext);
            }
            else
                reponseHandle.response_error(Error_WTF, responseContext);
        }
        else
            reponseHandle.response_error(Error_WTF, responseContext);

    } break;

    case ClientType::Teacher:
    {
        SqlCheckIsUserCreatorByCourseId queryIsUserListener(clientDatabaseId, courseid);
        if(mSqlController->executeQuery(queryIsUserListener) && queryIsUserListener.getResult())
        {
            SqlGetLecturePreviewList queryGetLecturePreviewList(courseid);
            if(mSqlController->executeQuery(queryGetLecturePreviewList))
            {
               bool isErrorOccurs;
                QVector<Lecture> result = queryGetLecturePreviewList.getResult();

                for (Lecture& lecture : result)
                {
                    SqlCheckIsLectureIsDone queryCheckIsLectureDone(clientDatabaseId, lecture.IdByRef());
                    if(!mSqlController->executeQuery(queryCheckIsLectureDone))
                    {isErrorOccurs =true; break;}
                    lecture.setIsLectureDone(queryCheckIsLectureDone.getResult());
                }

                if(isErrorOccurs)
                    reponseHandle.response_error(Error_WTF, responseContext);
                else
                    reponseHandle.response_getLecturePreviewList(result, responseContext);
            }
            else
                reponseHandle.response_error(Error_WTF, responseContext);
        }
        else
            reponseHandle.response_error(Error_WTF, responseContext);
    } break;

    default:
        reponseHandle.response_error(Error_WTF, responseContext);
    }
}

QString CTextStorageSubCtrl::getTestQuestionAsJson( const Test& test)
{
    QJsonObject jsonObject;
    QJsonArray jsonQuestionList;
    if ( test.QuestionListByRef().empty() ) return QString();

    for(int i = 0; i < test.QuestionListByRef().size(); ++i )
    {
        const TestQuestion& question = test.QuestionListByRef()[i];
        QJsonObject questionJsonObject;
        questionJsonObject["Id"] = i;
        questionJsonObject["Text"] = question.Text();
        questionJsonObject["QuestionType"] = question.QuestionType();

        if (false == question.AnswerListByRef().empty())
        {
            QJsonArray jsonAnswerList;
            for(int iAnswer = 0; iAnswer < question.AnswerListByRef().size(); ++iAnswer )
            {
                const TestAnswer& answer = question.AnswerListByRef()[iAnswer];
                QJsonObject answerJsonObject;
                answerJsonObject["Id"] = iAnswer;

                if(answer.__isset.text) answerJsonObject["Text"] = answer.TextByRef();
                if(answer.__isset.isRightAnswer)answerJsonObject["IsRightAnswer"] = answer.IsRightAnswer();
                //
                jsonAnswerList.append(answerJsonObject);
            }
            questionJsonObject["AnswerList"] = jsonAnswerList;
        }
        //
        jsonQuestionList.append(questionJsonObject);
    }

    jsonObject["QuestionList"] = jsonQuestionList;

    QJsonDocument saveDoc(jsonObject);
    return QString (saveDoc.toJson());
}

QVector<TestQuestion> CTextStorageSubCtrl::getTestQuestionFromJson( const QString& jsonQuestions, bool ignoreRightAnswer)
{
    if (jsonQuestions.isEmpty()) return QVector<TestQuestion>();

    QVector<TestQuestion> result;
    QJsonDocument loadDoc = QJsonDocument::fromJson(jsonQuestions.toUtf8());
    QJsonObject jsonObject = loadDoc.object();

    if (jsonObject.contains("QuestionList") && jsonObject["QuestionList"].isArray())
    {
        QJsonArray guestionList = jsonObject["QuestionList"].toArray();
        for ( int iQuestion = 0 ; iQuestion< guestionList.size(); ++iQuestion)
        {
            TestQuestion question;
            QJsonObject questionObject = guestionList[iQuestion].toObject();

            if (questionObject.contains("Id") && questionObject["Id"].isDouble())
            {
                question.setId(questionObject["Id"].toInt());
            }
            if (questionObject.contains("Text") && questionObject["Text"].isString())
            {
                question.setText(questionObject["Text"].toString());
            }
            if (questionObject.contains("QuestionType") && questionObject["QuestionType"].isDouble())
            {
                question.setQuestionType(TestQuestionType(questionObject["QuestionType"].toInt()));
            }

            if (questionObject.contains("AnswerList") && questionObject["AnswerList"].isArray())
            {
                QVector<TestAnswer> answerList;
                QJsonArray answerListJson = questionObject["AnswerList"].toArray();
                for ( int iAnswer = 0 ; iAnswer< answerListJson.size(); ++iAnswer)
                {
                    TestAnswer answer;
                    QJsonObject answerObject = answerListJson[iAnswer].toObject();

                    if (answerObject.contains("Id") && answerObject["Id"].isDouble())
                    {
                        answer.setId(answerObject["Id"].toInt());
                    }
                    if (answerObject.contains("Text") && answerObject["Text"].isString())
                    {
                        answer.setText(answerObject["Text"].toString());
                    }
                    if (false == ignoreRightAnswer && answerObject.contains("IsRightAnswer") && answerObject["IsRightAnswer"].isBool())
                    {
                        answer.setIsRightAnswer(answerObject["IsRightAnswer"].toBool());
                    }
                    answerList.push_back(answer);
                }
                question.setAnswerList(answerList);
            }

            result.push_back(question);
        }
    }

    return result;
}

