#include "qtask.h"

QTask::QTask(QObject *parent) : QObject(parent)
{
    _pid = 0;
    _threads = 0;
    _mem = 0;
    _cpu = 0;
    _user = "";
    _state = "";
    _command = "";
}
QTask::~QTask(){}

void QTask::setPid(int pid){
    _pid = pid;
}
void QTask::setThreads(int threads){
    _threads = threads;
}
void QTask::setMem(float mem){
    _mem = mem;
}
void QTask::setCPU(float cpu){
    _cpu = cpu;
}
void QTask::setUser(QString user){
    _user = user;
}
void QTask::setState(QString state){
    _state = state;
}
void QTask::setCommand(QString command){
    _command = command;
}

bool QTask::killProcess(){
    return kill(_pid, SIGKILL);
}

int QTask::pid(){
    return _pid;
}
int QTask::threads(){
    return _threads;
}
float QTask::mem(){
    return _mem;
}
float QTask::cpu(){
    return _cpu;
}
QString QTask::user(){
    return _user;
}
QString QTask::state(){
    return _state;
}
QString QTask::command(){
    return _command;
}

void QTask::checkCPU(){
    int cputotal = getTotalCPU();
    int cpuproc = getProcCPU(_pid);
    for (int i = 0; i < 1; i++){
        int prev_cputotal = cputotal;
        int prev_cpuproc = cpuproc;
        cputotal = getTotalCPU();
        cpuproc = getProcCPU(_pid);
        try{
            float res = ((float)cpuproc - (float)prev_cpuproc) / ((float)cputotal - (float)prev_cputotal);
            setCPU(res);
        }
        catch (std::logic_error err){
            setCPU(0.0f);
        }
    }
}
int QTask::getTotalCPU(){
    QFile file("/proc/stat");
    int result = 0;
    if (file.open(QIODevice::ReadOnly)){
        QTextStream stream(file.readAll());
        QString str = stream.readLine();
        QString loc = "";
        for (int i = 5; i < str.size(); i++){
            if (str.at(i) == ' '){
                result += loc.toInt();
                loc = "";
                i++;
            }
            else
                loc += str.at(i);
        }
    }
    if (file.isOpen())
        file.close();
    return result;
}
int QTask::getProcCPU(int pid){
    QFile file("/proc/" + QString::number(pid) + "/stat");
    int result = 0;
    if (file.open(QIODevice::ReadOnly)){
        QTextStream stream(file.readAll());
        QString str = stream.readLine();
        QString loc = "";
        int i = 0;
        int s_couner = 0;
        while (s_couner != 13) {
            if (str[i] == ' ')
                s_couner++;
            i++;
        }
        s_couner = 0;
        while (s_couner != 2) {
            if (str[i] == " "){
                s_couner++;
                result += loc.toInt();
                loc = "";
                i++;
            }
            loc += str[i];
            i++;
        }
    }
    if (file.isOpen())
        file.close();
    return result;
}

