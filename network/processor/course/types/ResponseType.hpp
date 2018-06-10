#ifndef RESPONSETYPE_HPP
#define RESPONSETYPE_HPP

enum ResponseType
{
    Response_Unknown = 1000,
    Response_SignIn,
    Response_SignUp,
    Response_GetTopicList,
    Response_GetCourseList,
    Response_SubscribeOnCourse,
    Response_CreateCourse,

    Response_CreateLecture,
    Response_GetLecturePreviewList,
    Response_GetLecture,

    Response_CreateTest,
    Response_GetTest
};


#endif // RESPONSETYPE_HPP
