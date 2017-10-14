#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _processes.readProcDir();
    initTable();

    QShortcut *sh_cut = new QShortcut(QKeySequence::Find, this);
    //sh_cut.setKey(QKeySequence::Find);

    register struct passwd *pwd;
    pwd = getpwuid(getuid());
    if (pwd)
        _username = QString::fromStdString(pwd->pw_name);

    connect(ui->processTable, SIGNAL(cellClicked(int,int)), this, SLOT(selectedItem(int,int)));
    connect(ui->killPutton, SIGNAL(clicked(bool)), this, SLOT(killProcess()));
    connect(sh_cut, SIGNAL(activated()), this, SLOT(showFindDialog()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initTable(){
    QList<QTask*> list_loc = _processes.getList();
    for (auto it = list_loc.begin(); it != list_loc.end(); ++it){
        initRow(ui->processTable->rowCount() - 1, *it);
        ui->processTable->setRowCount(ui->processTable->rowCount() + 1);
    }
    ui->processTable->setRowCount(ui->processTable->rowCount() - 1);
}
void MainWindow::initRow(int row, QTask *t){
    QTableWidgetItem *pid = new QTableWidgetItem(QString::number(t->pid()));
    QTableWidgetItem *user = new QTableWidgetItem(t->user());
    QTableWidgetItem *threads = new QTableWidgetItem(QString::number(t->threads()));
    QTableWidgetItem *mem = new QTableWidgetItem(QString::number((double)t->mem()));
    QTableWidgetItem *cpu = new QTableWidgetItem(QString::number((double)t->cpu()));
    QTableWidgetItem *command = new QTableWidgetItem(t->command());

    ui->processTable->setItem(row, 0, pid);
    ui->processTable->setItem(row, 1, user);
    ui->processTable->setItem(row, 2, threads);
    ui->processTable->setItem(row, 3, mem);
    ui->processTable->setItem(row, 4, cpu);
    ui->processTable->setItem(row, 5, command);
}

void MainWindow::selectedItem(int r, int c){
    _row = r;
    _col = c;
}
void MainWindow::killProcess(){
    if (_row >= 0 && _col >= 0){
        QTableWidgetItem *item = ui->processTable->item(_row, 0);
        int pid = item->text().toInt();
        item = ui->processTable->item(_row, 1);
        if (_username != "root" && (item->text() != _username))
            QMessageBox::critical(this, "Error", "You don't have a rights to kill this process.");
        else if (_username == item->text() || _username == "root"){
            _processes.killProcess(pid);
            ui->processTable->removeRow(_row);
            _processes.delFromList(_row);
            _row = -1;
            _col = -1;
        }
    }
}
void MainWindow::newProcess(){}
void MainWindow::showFindDialog(){
    FindDialog *fd = new FindDialog(this, ui->processTable);
    fd->show();
}
