#include "singleeva.h"
#include "ui_singleeva.h"
#include <QDebug>
//#include "DataProcessing/DataHandler.h"



Singleeva::Singleeva(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Singleeva)
{
    ui->setupUi(this);
     connect(ui->pushButton, &QPushButton::clicked, this, &Singleeva::on_pushButton_clicked);
}

Singleeva::~Singleeva()
{
    delete ui;
}


// single evaluate page evaluate button
void Singleeva::on_pushButton_clicked()
{
    // Collect data from QLineEdit widgets
    QString purpose = ui->lineEdit1->text();
    QString interest_rate = ui->lineEdit2->text();
    QString installment = ui->lineEdit3->text();
    QString log_annual_income = ui->lineEdit4->text();
    QString debt_to_income = ui->lineEdit5->text();
    QString fico_score = ui->lineEdit6->text();
    QString days_with_credit_line = ui->lineEdit7->text();
    QString revolving_balance = ui->lineEdit8->text();
    QString revolving_utilization_rate = ui->lineEdit9->text();
    QString inquiries_last_6_months = ui->lineEdit10->text();
    QString past_due_last_2_years = ui->lineEdit11->text();
    QString derogatory_public_records = ui->lineEdit12->text();
    QString not_fully_paid = ui->lineEdit13->text();

    // Construct a row of data
    std::vector<std::string> rowData = {
        purpose.toStdString(),
        interest_rate.toStdString(),
        installment.toStdString(),
        log_annual_income.toStdString(),
        debt_to_income.toStdString(),
        fico_score.toStdString(),
        days_with_credit_line.toStdString(),
        revolving_balance.toStdString(),
        revolving_utilization_rate.toStdString(),
        inquiries_last_6_months.toStdString(),
        past_due_last_2_years.toStdString(),
        derogatory_public_records.toStdString(),
        not_fully_paid.toStdString()
    };

    // Append the row of data to your main data vector
    data.push_back(rowData);

    // Call the function with the data vector
    // FunctionName(data);
    // processData(data);

     // Show the result based on the processed data
   /* bool result = processData(data);
    ui->textLabel->setText(result ? "Y" : "N");*/

    // Clear line edits for the next entry if needed
    ui->lineEdit1->clear();
    ui->lineEdit2->clear();
    ui->lineEdit3->clear();
    ui->lineEdit4->clear();
    ui->lineEdit5->clear();
    ui->lineEdit6->clear();
    ui->lineEdit7->clear();
    ui->lineEdit8->clear();
    ui->lineEdit9->clear();
    ui->lineEdit10->clear();
    ui->lineEdit11->clear();
    ui->lineEdit12->clear();
    ui->lineEdit13->clear();
}






