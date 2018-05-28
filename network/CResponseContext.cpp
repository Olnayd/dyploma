#include "CResponseContext.hpp"

CResponseContext::CResponseContext(const std::shared_ptr<CNetworkClient> clientPtr_, const quint32 responseId_, const quint32 seqId_)
    : clientPtr(clientPtr_), responseId(responseId_), seqId(seqId_) {}
