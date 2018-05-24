#include "JobQueue.hpp"

JobQueue::JobQueue()
{
    connect(this, SIGNAL(nextJob()),
            this,   SLOT(startProcessJob()));
    connect(this, SIGNAL(endJob()),
            this,   SLOT(endProcessJob()));
}

int JobQueue::addJob(const IJob& userJob)
{
    static int sProcessingJobsCounter = 0;
    sProcessingJobsCounter++;

    mPendingJobs.push(userJob);
    emit newJob();
    return sProcessingJobsCounter;
}

void JobQueue::startProcessJob()
{
    if( nullptr == mWorkingJob          &&
        false   == mPendingJobs.empty() )
    {
        mWorkingJob = &mPendingJobs.top();

        connect (mWorkingJob, SIGNAL(initialised()),
                 this,          SLOT(job_initialised()));
        connect (mWorkingJob, SIGNAL(executed()),
                 this,          SLOT(job_executed()));
        connect (mWorkingJob, SIGNAL(preparedForShutdown()),
                 this,          SLOT(job_preparedForShutdown()));

        connect (this,        SIGNAL(job_init()),
                 mWorkingJob,   SLOT(m_initialise()));
        connect (this,        SIGNAL(job_execute()),
                 mWorkingJob,   SLOT(m_execute()));
        connect (this,        SIGNAL(job_prepareShutdown()),
                 mWorkingJob,   SLOT(m_prepareShutdown()));

        emit job_init();
    };
}

void JobQueue::endProcessJob()
{
    if ( mWorkingJob != nullptr)
    {
        disconnect( mWorkingJob, SIGNAL(initialised()),
                    this,          SLOT(job_initialised()));
        disconnect( mWorkingJob, SIGNAL(executed()),
                    this,          SLOT(job_executed()));
        disconnect( mWorkingJob, SIGNAL(preparedForShutdown()),
                    this,          SLOT(job_preparedForShutdown()));

        disconnect( this,        SIGNAL(job_init()),
                    mWorkingJob,   SLOT(m_initialise()));
        disconnect( this,        SIGNAL(job_execute()),
                    mWorkingJob,   SLOT(m_execute()));
        disconnect( this,        SIGNAL(job_prepareShutdown()),
                    mWorkingJob,   SLOT(m_prepareShutdown()));

        mWorkingJob = nullptr;
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
