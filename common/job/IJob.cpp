#include "IJob.h"

IJob::IJob()
{

}

void IJob::initialised()
{
    if (!mIsInitialised)
    {
        mIsInitialised = true;
        emit initialised();
    }
}

void IJob::preparedForShutdown()
{
    if (!mIsPreparedForShutdown)
    {
        mIsPreparedForShutdown = true;
        emit sig_preparedForShutdown();
    }
}

void IJob::slot_initialise()
{
    mIsInitialised = init();
    if (mIsInitialised)
    {
        emit sig_initialised();
    }
}

void IJob::slot_execute()
{
    if (mIsInitialised && !mIsExecuted)
    {
        execute();
        mIsExecuted = true;
        emit sig_executed();
    }

}

void IJob::slot_prepareForShutdown()
{
    if (mIsInitialised && mIsExecuted && !mIsPreparedForShutdown)
    {
        mIsPreparedForShutdown = prepareForShutdown();
        if (mIsPreparedForShutdown)
        {
            emit sig_preparedForShutdown();
        }
    }
}
