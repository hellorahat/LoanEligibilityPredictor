#include "evaluate.h"
#include "ui_evaluate.h"
#include "single.h"
#include "bulk.h"

evaluate::evaluate(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::evaluate)
{
    ui->setupUi(this);
}

evaluate::~evaluate()
{
    delete ui;
}

void evaluate::on_pushButton_clicked()
{
    single sing;
    sing.exec();
}


void evaluate::on_pushButton_2_clicked()
{
    bulk bul;
    bul.exec();
}

