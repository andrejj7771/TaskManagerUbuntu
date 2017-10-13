#ifndef PROCLIST_H
#define PROCLIST_H

#include <stdlib.h>
#include <unistd.h>
#include <qtask.h>
#include <stdio.h>
#include <pwd.h>

#include <QFileInfo>
#include <QObject>
#include <QDebug>
#include <QFile>
#include <QList>
#include <QDir>

class ProcList : public QObject
{
    Q_OBJECT
public:
    explicit ProcList(QObject *parent = nullptr);
    ~ProcList();

    void delFromList(int index);
    QList<QTask*> getList();        //get process list

public slots:
    void killProcess(int pid);
    void readProcDir();             //read /proc/[PID]/status file

private:
    QList<QTask*> _taskList;        //process list
    QFileInfoList FIL;              // /proc/[PID]/ directories

    QString getUserName(uint uid);  //get Username by userID

signals:
};

#endif // PROCLIST_H
