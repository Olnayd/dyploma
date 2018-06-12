#ifndef RESPONSETYPE_HPP
#define RESPONSETYPE_HPP

#include<QDataStream>

enum ResponseType
{
    Response_Unknown = 1000,
    Response_SignIn,
    Response_SignUp,
    Response_SubscribeOnCourse,
    Response_CreateCourse,
    Response_CreateTest,
    Response_CreateLecture,
    Response_FinishLection,
    Response_FinishTest,
    Response_GetTopicList,
    Response_GetCourseList,
    Response_GetLecturePreviewList,
    Response_GetLecture,
    Response_GetTest
};

QDataStream& operator>>(QDataStream& stream, ResponseType& type);
QDataStream& operator<<(QDataStream& stream, const ResponseType& type);


#endif // RESPONSETYPE_HPP
