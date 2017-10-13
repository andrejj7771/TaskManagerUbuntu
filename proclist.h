#ifndef PROCLIST_H
#define PROCLIST_H

#include <qtask.h>

#include <QObject>
#include <QFile>
#include <QList>
#include <QDir>

class ProcList : public QObject
{
    Q_OBJECT
public:
    explicit ProcList(QObject *parent = nullptr);

    void readProcDir();

private:
    QList<QTask> _taskList;
    QFileInfoList FIL;

    QString getUserName(uint uid);

signals:

public slots:
};

#endif // PROCLIST_H
