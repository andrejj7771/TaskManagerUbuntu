#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QTableWidgetItem>
#include <QTableWidget>
#include <QMessageBox>
#include <QModelIndex>
#include <QDialog>

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
    QTableWidget *table;
    Ui::FindDialog *ui;

    void addToCB();

private slots:
    QTableWidget *find();
};

#endif // FINDDIALOG_H
