#ifndef IJOB_H
#define IJOB_H


class IJob
{


signals:
    void initialised();
    void executed();
    void preparedForShutdown();

public slots:
    void m_initialise();
    void m_execute();
    void m_prepareShutdown();

public:
    IJob();
};

#endif // IJOB_H
