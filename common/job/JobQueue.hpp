#ifndef JOBQUEUE_H
#define JOBQUEUE_H

#include <QObject>
#include <stack>
#include <memory>
#include "IJob.h"

class JobQueue : public QObject
{
    Q_OBJECT
    int addJob( std::shared_ptr<IJob>&);


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

    std::shared_ptr<IJob> mWorkingJob;
    std::stack<std::shared_ptr<IJob>> mPendingJobs;
};

#endif // JOBQUEUE_H
