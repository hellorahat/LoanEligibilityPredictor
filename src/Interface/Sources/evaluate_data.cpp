#include "evaluate_data.h"
#include "ui_evaluate_data.h"

Evaluate_Data::Evaluate_Data(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Evaluate_Data)
{
    ui->setupUi(this);
}

Evaluate_Data::~Evaluate_Data()
{
    delete ui;
}

// open Single Evaluation page by click Single Evaluation
void Evaluate_Data::on_Singleeva_clicked()
{
    Singleeva single;
    single.setModal(true);
    single.exec();
}


// open Bulk Evaluation page by click Bulk Evaluation
void Evaluate_Data::on_pushButton_2_clicked()
{
    Bulkeva bulk;
    bulk.setModal(true);
    bulk.exec();
}

