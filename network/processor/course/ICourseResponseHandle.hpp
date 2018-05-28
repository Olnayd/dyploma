#ifndef ICOURSERESPONSEHANDLE_HPP
#define ICOURSERESPONSEHANDLE_HPP

#include "CourseTypes.h"
#include "network/CResponseContext.hpp"

class ICourseResponseHandle
{
public:
    virtual void response_signIn(const ClientInformation& clientInfo, const CResponseContext& responseContext) = 0 ;
    virtual void response_signUp(const bool result, const CResponseContext& responseContext) = 0 ;
    //just for testing
    virtual void response_getCourseInfo(const CResponseContext& responseContext) = 0;


    virtual void response_error(const quint32 errorCode, const CResponseContext& responseContex) = 0;
};

#endif // ICOURSERESPONSEHANDLE_HPP
