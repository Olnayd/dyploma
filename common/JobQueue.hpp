#ifndef JOBQUEUE_H
#define JOBQUEUE_H

#include <QObject>
#include <stack>
#include "IJob.h"

class JobQueue : public QObject
{
    int addJob(const IJob&);


signals:
    void endJob();
    void nextJob();

    void job_init();
    void job_execute();
    void job_prepareShutdown();

private slots:
    void startProcessJob();
    void endProcessJob();

    void job_initialised();
    void job_executed();
    void job_preparedForShutdown();

public:
    JobQueue();

    IJob* mWorkingJob;
    std::stack<IJob> mPendingJobs;
};

#endif // JOBQUEUE_H
