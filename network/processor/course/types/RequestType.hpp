#ifndef REQUESTTYPE_HPP
#define REQUESTTYPE_HPP

#include<QDataStream>

enum RequestType
{
    Request_Unknown = 0,
    Request_SignIn,
    Request_SignUp,
    Request_SubscribeOnCourse,
    Request_CreateLecture,
    Request_CreateCourse,
    Request_CreateTest,
    Request_FinishLecture,
    Request_FinishTest,
    Request_GetTopicList,
    Request_GetCourseList,
    Request_GetCourseListByFilter,
    Request_GetLecturePreviewList,
    Request_GetLecture,
    Request_GetTest
};

QDataStream& operator>>(QDataStream& stream, RequestType& type);
QDataStream& operator<<(QDataStream& stream, const RequestType& type);


#endif // REQUESTTYPE_HPP
