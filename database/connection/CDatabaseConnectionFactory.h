#ifndef CSTORAGEFACTORY_H
#define CSTORAGEFACTORY_H

#include <memory>
#include "CDatabaseConnection.h"
#include "EStorage.h"

class CDatabaseConnectionFactory
{
public:
    static ::std::shared_ptr<CDatabaseConnection> getConnection(EStorage storageType);
};

#endif // CSTORAGEFACTORY_H
