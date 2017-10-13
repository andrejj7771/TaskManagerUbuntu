#include "finddialog.h"
#include "ui_finddialog.h"

FindDialog::FindDialog(QWidget *parent, QTableWidget*t) :
    QDialog(parent),
    ui(new Ui::FindDialog)
{
    ui->setupUi(this);
    ui->pushButton->setShortcut(QKeySequence("Return"));
    table = t;

    addToCB();

    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(find()));
    connect(this, SIGNAL(isFound()), this, SLOT(close()));
}

FindDialog::~FindDialog()
{
    delete ui;
}

QTableWidget* FindDialog::find(){
    table->clearSelection();
    QTableWidget *tmp = new QTableWidget();
    if (!ui->lineEdit->text().isEmpty())
        for (int i = 0; i < table->rowCount(); i++)
            if (table->item(i, ui->comboBox->currentIndex())->text().contains(ui->lineEdit->text())){
                table->selectRow(i);
                //QModelIndex tmp = table->model()->index(i, ui->comboBox->currentIndex());
                //table->selectionModel()->select(tmp, QItemSelectionModel::Select);
            }
    else QMessageBox::warning(this, "Error", "Empty string");
    return table;
}

void FindDialog::addToCB(){
    for (int i = 0; i < table->columnCount(); i++)
        ui->comboBox->addItem(table->horizontalHeaderItem(i)->text());
}
