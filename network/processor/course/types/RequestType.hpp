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
    Request_CreateLection,
    Request_GetLectionPreviewList,
    Request_GetLection

};

#endif // REQUESTTYPE_HPP
