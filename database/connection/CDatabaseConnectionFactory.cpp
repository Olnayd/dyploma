
#include <map>
#include "CDatabaseConnectionFactory.h"

#include <memory>

static std::map<EStorage, ::std::shared_ptr<CDatabaseConnection>> sStorageMap;

::std::shared_ptr<CDatabaseConnection> createStorage(EStorage storageType)
{
    ::std::shared_ptr<CDatabaseConnection> result;

    switch (storageType)
    {
        case TEXT_STORAGE:   result = ::std::make_shared<CDatabaseConnection>("CourseStorage.db", "database/", "QSQLITE" ); break;
        case IMAGE_STORAGE:  result = ::std::make_shared<CDatabaseConnection>("ImageStorage.db" , "database/", "QSQLITE" ); break;
    }

    return result;
}

::std::shared_ptr<CDatabaseConnection> CDatabaseConnectionFactory::getConnection(EStorage storageType)
{
    auto& storage = sStorageMap[storageType];
    if (storage == nullptr)
    {
        storage = createStorage(storageType);
    }

    return storage;
}
