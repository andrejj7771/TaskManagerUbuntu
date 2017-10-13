#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QModelIndex>

namespace Ui {
class FindDialog;
}

class FindDialog : public QDialog
{
    Q_OBJECT

signals:
    void isFound();

public:
    explicit FindDialog(QWidget *parent = 0, QTableWidget *t = nullptr);
    ~FindDialog();

private:
    Ui::FindDialog *ui;
    QTableWidget *table;

    void addToCB();

private slots:
    QTableWidget *find();
};

#endif // FINDDIALOG_H
