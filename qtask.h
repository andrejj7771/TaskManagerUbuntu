#ifndef QTASK_H
#define QTASK_H

#include <signal.h>

#include <QObject>
#include <QDateTime>
#include <QTextStream>
#include <QFile>

class QTask : public QObject
{
    Q_OBJECT
public:
    explicit QTask(QObject *parent = nullptr);
    ~QTask();

    void setPid(int pid);
    void setThreads(int threads);
    void setPriority(int priority);
    void setNice(short nice);
    void setSize(int size);
    void setRes(int res);
    void setMem(float mem);
    void setCPU(float cpu);
    void setTime(QDateTime time);
    void setUser(QString user);
    void setState(QString state);
    void setCommand(QString command);
    void setName(QString name);

    bool killProcess();

    int pid();
    int threads();
    int priority();
    int size();
    int res();
    short nice();
    float mem();
    float cpu();
    QDateTime time();
    QString user();
    QString state();
    QString command();
    void checkCPU();

private:
    int _pid; //+
    int _threads; //+
    int _priority;
    int _size;
    int _res;
    short _nice;
    float _mem;
    float _cpu;

    QDateTime _time;
    QString _user; //+
    QString _state; //+
    QString _command; //+

    int getTotalCPU();
    int getProcCPU(int pid);


signals:

public slots:
};

#endif // QTASK_H
