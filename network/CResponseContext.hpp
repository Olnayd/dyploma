#ifndef CRESPONSECONTEXT_H
#define CRESPONSECONTEXT_H

#include<memory>
#include "CNetworkClient.hpp"

class CResponseContext
{
public:
    CResponseContext(const std::shared_ptr<CNetworkClient> clientPtr_, const quint32 responseId_, const quint32 seqId_);

    const std::shared_ptr<CNetworkClient> clientPtr;
    const quint32 responseId;
    const quint32 seqId;
};

#endif // CRESPONSECONTEXT_H
