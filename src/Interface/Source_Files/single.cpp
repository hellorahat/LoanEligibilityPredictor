#include "single.h"
#include "ui_single.h"

single::single(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::single)
{
    ui->setupUi(this);
}

single::~single()
{
    delete ui;
}

void single::on_pushButton_clicked()
{
    // Collect data from QLineEdit widgets
    QString cridet_policy = ui->lineEdit->text();
    QString purpose = ui->lineEdit_2->text();
    QString interest_rate = ui->lineEdit_3->text();
    QString installment = ui->lineEdit_4->text();
    QString log_annual_income = ui->lineEdit_5->text();
    QString debt_to_income = ui->lineEdit_6->text();
    QString fico_score = ui->lineEdit_7->text();
    QString days_with_credit_line = ui->lineEdit_8->text();
    QString revolving_balance = ui->lineEdit_9->text();
    QString revolving_utilization_rate = ui->lineEdit_10->text();
    QString inquiries_last_6_months = ui->lineEdit_11->text();
    QString past_due_last_2_years = ui->lineEdit_12->text();
    QString derogatory_public_records = ui->lineEdit_13->text();
    QString not_fully_paid = ui->lineEdit_14->text();

    // Construct a row of data
    std::vector<std::string> rowData = {
        cridet_policy.toStdString(),
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
    //data.push_back(rowData);

    // Call the function with the data vector
    // FunctionName(data);
    // processData(data);

    // Show the result based on the processed data
    //bool result = processData(data);
    //ui->textLabel->setText(result ? "Y" : "N");


    // Clear line edits for the next entry if needed
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
    ui->lineEdit_7->clear();
    ui->lineEdit_8->clear();
    ui->lineEdit_9->clear();
    ui->lineEdit_10->clear();
    ui->lineEdit_11->clear();
    ui->lineEdit_12->clear();
    ui->lineEdit_13->clear();
    ui->lineEdit_14->clear();
}

