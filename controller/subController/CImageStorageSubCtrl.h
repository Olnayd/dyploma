#ifndef CIMAGESTORAGESUBCTRL_H
#define CIMAGESTORAGESUBCTRL_H

#include "controller/subController/CSqlSubCtrl.h"
#include "common/controller/CSubController.h"


class CImageStorageSubCtrl : public common::controller::CSubController
{
public:
    CImageStorageSubCtrl( std::shared_ptr<CSqlSubCtrl> sqlController );
    virtual bool init() override final;
    virtual const char* getName() override final;
    virtual bool prepareShutdown() override final;

private:
    std::shared_ptr<CSqlSubCtrl> mSqlController;
};

#endif // CIMAGESTORAGESUBCTRL_H
