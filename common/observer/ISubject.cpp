#include "ISubject.h"
#include <algorithm>

using namespace common::observer;

ISubject::~ISubject()
{
    for ( auto obsPtr : mObserverList)
    {
        dettach(obsPtr);
    }
}

void ISubject::attach(IObserver* obs)
{
    mObserverList.insert(mObserverList.end(), obs);
}

void ISubject::dettach(IObserver* obs)
{
   auto obsIt = std::find(mObserverList.begin(), mObserverList.end(), obs);
   if(obsIt != mObserverList.end())
       mObserverList.erase(obsIt);
}

void ISubject::notify()
{
    for ( auto obsPtr : mObserverList)
    {
        obsPtr->update();
    }
}
