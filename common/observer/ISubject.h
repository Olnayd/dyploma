#ifndef ISUBJECT_H
#define ISUBJECT_H

#include <memory>
#include <vector>
#include "IObserver.h"

namespace common
{
    namespace observer
    {
        class ISubject
        {
        public:
            ISubject() = default;
            virtual ~ISubject();

            void attach( IObserver* );
            void dettach( IObserver* );
            void notify();
        public:
            std::vector<IObserver*> mObserverList;
        };

    }
}


#endif // ISUBJECT_H
