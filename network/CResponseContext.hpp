#ifndef CRESPONSECONTEXT_H
#define CRESPONSECONTEXT_H

#include<memory>
#include "CNetworkClient.hpp"
#include "processor/course/types/ResponseType.hpp"

class CResponseContext
{
public:
    CResponseContext(const std::shared_ptr<CNetworkClient> clientPtr_, const ResponseType responseId_, const quint32 seqId_);

    const std::shared_ptr<CNetworkClient> clientPtr;
    const ResponseType responseId;
    const quint32 seqId;
};

#endif // CRESPONSECONTEXT_H
