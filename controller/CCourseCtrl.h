#ifndef CCOURSECTRL_H
#define CCOURSECTRL_H

#include <map>
#include "database/connection/EStorage.h"
#include "common/controller/CController.h"
#include "subController/CSqlSubCtrl.h"
#include "subController/CImageStorageSubCtrl.h"
#include "subController/CTextStorageSubCtrl.h"

class CCourseCtrl : public common::controller::CController
{
public:
    CCourseCtrl();

    bool init() override;
    bool prepareShutdown() override;
    const char* getName() override;

private:
    std::shared_ptr<CSqlSubController> mSqlController;
    std::shared_ptr<CTextStorageSubCtrl> mTextController;
    std::shared_ptr<CImageStorageSubCtrl> mImageController;


};

#endif // CCOURSECTRL_H
