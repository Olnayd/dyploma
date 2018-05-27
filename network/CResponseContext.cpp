#include "CResponseContext.hpp"

CResponseContext::CResponseContext(const quint32 clientId_, const quint32 responseId_, const quint32 seqId_)
    : clientId(clientId_), responseId(responseId_), seqId(seqId_) {}
