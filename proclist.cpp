#include "proclist.h"
#include <QDebug>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>

ProcList::ProcList(QObject *parent) : QObject(parent)
{

}

void ProcList::readProcDir(){
    QDir dir("/proc");
    dir.setFilter(QDir::Dirs);
    QFileInfoList IL = dir.entryInfoList();
    for (int i = 0; i < IL.size(); ++i) {
        QTask *tmp_task = new QTask();
        QFileInfo fileInfo = IL.at(i);
        if(fileInfo.fileName().toInt() >= 1){
            QFile tmp_file(fileInfo.filePath() + "/status");
            if (tmp_file.open(QIODevice::ReadOnly)){
                QTextStream stream(tmp_file.readAll(), QIODevice::ReadOnly);
                while(!stream.atEnd()){
                    QString line = stream.readLine();
                    QString arg;
                    for(int j = line.indexOf(':') + 2; j < line.size(); j++){
                        arg += line.at(j);
                        if (line.at(j) == '\t')
                            j = line.size() - 1;
                    }
                    if (line.contains("Name"))
                        tmp_task->setCommand(arg);
                    else if (line.contains("State"))
                        tmp_task->setState(arg);
                    else if (line.contains("Pid"))
                        tmp_task->setPid(arg.toInt());
                    else if (line.contains("Threads"))
                        tmp_task->setThreads(arg.toInt());
                    else if (line.contains("Uid"))
                        tmp_task->setUser(getUserName(arg.toUInt()));
                    else if (line.contains("VmSize"))
                        tmp_task->setMem(arg.toFloat());

                }
            }
            if (tmp_file.isOpen())
                tmp_file.close();
        }
    }
}
QString ProcList::getUserName(uint uid){
    register struct passwd *pwd;
    pwd = getpwuid(uid);
    if (pwd)
        return QString::fromStdString(pwd->pw_name);
    else return "";
}
