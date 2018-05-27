#ifndef CRESPONSECONTEXT_H
#define CRESPONSECONTEXT_H

#include<qtypeinfo.h>

class CResponseContext
{
public:
    CResponseContext(const quint32 clientId_, const quint32 responseId_, const quint32 seqId_);

    const quint32 clientId;
    const quint32 responseId;
    const quint32 seqId;
};

#endif // CRESPONSECONTEXT_H
