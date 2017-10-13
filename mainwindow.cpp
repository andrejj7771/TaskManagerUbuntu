#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qtask.h"
#include "proclist.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ProcList l;
    l.readProcDir();
}

MainWindow::~MainWindow()
{
    delete ui;
}
