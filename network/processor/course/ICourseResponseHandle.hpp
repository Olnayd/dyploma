#ifndef ICOURSERESPONSEHANDLE_HPP
#define ICOURSERESPONSEHANDLE_HPP

#include "network/CResponseContext.hpp"

class ICourseResponseHandle
{
public:
    virtual void response_autorization(const bool result, const CResponseContext& responseContext) = 0 ;
    virtual void response_getCourseInfo(const CResponseContext& responseContext) = 0;


    virtual void response_error(const quint8 errorCode, const CResponseContext& responseContex) = 0;
};

#endif // ICOURSERESPONSEHANDLE_HPP
