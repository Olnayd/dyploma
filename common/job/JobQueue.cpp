#include "JobQueue.hpp"

JobQueue::JobQueue()
{
    connect(this, SIGNAL(nextJob()),
            this,   SLOT(startProcessJob()));
    connect(this, SIGNAL(endJob()),
            this,   SLOT(endProcessJob()));
}

int JobQueue::addJob( std::shared_ptr<IJob>& userJob)
{
    static int sProcessingJobsCounter = 0;
    sProcessingJobsCounter++;

    mPendingJobs.push(userJob);
    emit  nextJob();
    return sProcessingJobsCounter;
}

void JobQueue::startProcessJob()
{
    if( nullptr == mWorkingJob          &&
        false   == mPendingJobs.empty() )
    {
        mWorkingJob = mPendingJobs.top();

        connect (mWorkingJob.get(), SIGNAL(sig_initialised()),
                 this,          SLOT(job_initialised()));
        connect (mWorkingJob.get(), SIGNAL(sig_executed()),
                 this,          SLOT(job_executed()));
        connect (mWorkingJob.get(), SIGNAL(sig_preparedForShutdown()),
                 this,          SLOT(job_preparedForShutdown()));

        connect (this,        SIGNAL(job_init()),
                 mWorkingJob.get(),   SLOT(slot_initialise()));
        connect (this,        SIGNAL(job_execute()),
                 mWorkingJob.get(),   SLOT(slot_execute()));
        connect (this,        SIGNAL(job_prepareShutdown()),
                 mWorkingJob.get(),   SLOT(slot_prepareShutdown()));

        emit job_init();
    };
}

void JobQueue::endProcessJob()
{
    if ( mWorkingJob != nullptr)
    {
        disconnect( mWorkingJob.get(), SIGNAL(sig_initialised()),
                    this,          SLOT(job_initialised()));
        disconnect( mWorkingJob.get(), SIGNAL(sig_executed()),
                    this,          SLOT(job_executed()));
        disconnect( mWorkingJob.get(), SIGNAL(sig_preparedForShutdown()),
                    this,          SLOT(job_preparedForShutdown()));

        disconnect( this,        SIGNAL(job_init()),
                    mWorkingJob.get(),   SLOT(slot_initialise()));
        disconnect( this,        SIGNAL(job_execute()),
                    mWorkingJob.get(),   SLOT(slot_execute()));
        disconnect( this,        SIGNAL(job_prepareShutdown()),
                    mWorkingJob.get(),   SLOT(slot_prepareShutdown()));

        mWorkingJob.reset();
        mPendingJobs.pop();

        emit nextJob();
    }

}

void JobQueue::job_executed()
{
    emit job_prepareShutdown();
}
void JobQueue::job_initialised()
{
    emit job_execute();
}
void JobQueue::job_preparedForShutdown()
{
    emit endJob();
}
