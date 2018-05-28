#ifndef CTEXTSTORAGESUBCTRL_H
#define CTEXTSTORAGESUBCTRL_H

#include "common/controller/CSubController.h"
#include "controller/subController/CSqlSubCtrl.h"

class CTextStorageSubCtrl : public common::controller::CSubController
{
public:
    CTextStorageSubCtrl(std::shared_ptr<CSqlSubCtrl> sqlController);
    virtual bool init() override final;
    virtual const char* getName() override final;
    virtual bool prepareShutdown() override final;
private:
    std::shared_ptr<CSqlSubCtrl> mSqlController;
};

#endif // CTEXTSTORAGESUBCTRL_H
