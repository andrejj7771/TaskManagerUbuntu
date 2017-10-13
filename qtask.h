#ifndef QTASK_H
#define QTASK_H

#include <signal.h>

#include <QTextStream>
#include <QDateTime>
#include <QObject>
#include <QFile>

class QTask : public QObject
{
    Q_OBJECT
public:
    explicit QTask(QObject *parent = nullptr);
    ~QTask();

    void setCommand(QString command);
    void setThreads(int threads);
    void setState(QString state);
    void setUser(QString user);
    void setMem(float mem);
    void setCPU(float cpu);
    void setPid(int pid);

    QString command();
    QString state();
    QString user();
    int threads();
    float mem();
    float cpu();
    int pid();

    void checkCPU();

private:
    int _threads;       //threads quantity
    float _mem;         //used memory
    float _cpu;         //used CPU resources
    int _pid;           //process id
    QString _command;   //run command
    QString _state;     //state procces (Runnable, Sleet, etc)
    QString _user;      //user who ran a process

    int getProcCPU(int pid);
    int getTotalCPU();

signals:

public slots:
    bool killProcess();
};

#endif // QTASK_H
