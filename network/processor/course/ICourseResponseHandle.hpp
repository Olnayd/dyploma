#ifndef ICOURSERESPONSEHANDLE_HPP
#define ICOURSERESPONSEHANDLE_HPP

#include "types/ClientIdentificator.hpp"
#include "types/ClientInformation.hpp"
#include "types/ErrorType.hpp"
#include "types/CourseTopic.hpp"
#include "types/CourseInformation.hpp"
#include "network/CResponseContext.hpp"

class ICourseResponseHandle
{
public:
    virtual void response_signIn(const ClientInformation& clientInfo, const CResponseContext& responseContext) = 0 ;
    virtual void response_signUp(const bool result, const CResponseContext& responseContext) = 0 ;


    virtual void response_getTopicList( const QVector<CourseTopic>& topicList, const CResponseContext& responseContext) = 0;
    virtual void response_getCourseList( const QVector<CourseInformation>& courseList, const CResponseContext& responseContext) = 0;
    virtual void response_subscribeOnCourse(const bool result, const CResponseContext& responseContext) = 0;
    virtual void response_createLection( const quint32 courseid, const CResponseContext& responseContext) = 0;


    virtual void response_error(const ErrorType errorCode, const CResponseContext& responseContex) = 0;
};

#endif // ICOURSERESPONSEHANDLE_HPP
