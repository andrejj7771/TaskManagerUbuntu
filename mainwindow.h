#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QShortcut>
#include <QTimer>

#include "finddialog.h"
#include "proclist.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    ProcList _processes;
    Ui::MainWindow *ui;
    QString _username;

    int _row;
    int _col;

    void initRow(int row, QTask *t);
    void initTable();

private slots:
    void selectedItem(int r, int c);
    void showFindDialog();
    void killProcess();
    void newProcess();
};

#endif // MAINWINDOW_H
