#ifndef IJOB_H
#define IJOB_H

#include<QObject>

class IJob : public QObject
{
    Q_OBJECT
private:
    bool mIsInitialised;
    bool mIsExecuted;
    bool mIsPreparedForShutdown;

public:
    virtual bool init() = 0;
    virtual void execute() = 0;
    virtual bool prepareForShutdown() = 0;

    void initialised();
    void preparedForShutdown();

signals:
    void sig_initialised();
    void sig_executed();
    void sig_preparedForShutdown();

public slots:
    void slot_initialise();
    void slot_execute();
    void slot_prepareForShutdown();

public:
    IJob();
};

#endif // IJOB_H
