#ifndef CROOTCOMPONENT_H
#define CROOTCOMPONENT_H

#include <vector>
#include <memory>

#include "common/observer/IObserver.h"
#include "common/controller/CController.h"


class CRootComponent : public common::observer::IObserver
{
public:
    CRootComponent();
    void requestBoot();
    virtual void update() override final;

private:
    bool areAllControllersInitialized();
    bool areAllControllersFinishedPrepareShutdown();

private:
    bool mbIsApplicationReady;
    bool mbIsPrepareShutdownReady;
    std::vector< std::shared_ptr<common::controller::CController> > mCtrlList;
};

#endif // CROOTCOMPONENT_H
