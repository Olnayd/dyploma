#ifndef REQUESTTYPE_HPP
#define REQUESTTYPE_HPP

enum RequestType
{
    Request_Unknown = 0,
    Request_SignIn,
    Request_SignUp,
    Request_GetTopicList,
    Request_GetCourseList,
    Request_GetCourseListByFilter,
    Request_SubscribeOnCourse,
    Request_CreateCourse,

    Request_CreateLecture,
    Request_GetLecturePreviewList,
    Request_GetLecture

};

#endif // REQUESTTYPE_HPP
