#include "../Header_File/singleeva.h"
#include "../ui_singleeva.h"
#include <QDebug>
//#include "DataProcessing/DataHandler.h"



Singleeva::Singleeva(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Singleeva)
{
    ui->setupUi(this);

}

Singleeva::~Singleeva()
{
    delete ui;
}

// Function to convert QString to double using std::stod
double convertToDouble(const QString& str) {
    bool ok;
    double value = str.toDouble(&ok);
    if (!ok) {
        throw std::invalid_argument("Invalid argument: " + str.toStdString());
    }
    return value;
}

// single evaluate page evaluate button
void Singleeva::on_pushButton_clicked()
{
    try {
    // Collect data from QLineEdit widgets
    QString credit_policy = ui->lineEdit1_3->text();
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

    // Convert QString values to doubles and store in vector<double>
    std::vector<double> rowData = {
        convertToDouble(credit_policy),
        convertToDouble(purpose),
        convertToDouble(interest_rate),
        convertToDouble(installment),
        convertToDouble(log_annual_income),
        convertToDouble(debt_to_income),
        convertToDouble(fico_score),
        convertToDouble(days_with_credit_line),
        convertToDouble(revolving_balance),
        convertToDouble(revolving_utilization_rate),
        convertToDouble(inquiries_last_6_months),
        convertToDouble(past_due_last_2_years),
        convertToDouble(derogatory_public_records),
        convertToDouble(not_fully_paid)
    };

    bool result = true;
    QString labelText = "Data: ";
    for (size_t i = 0; i < rowData.size(); ++i) {
        labelText += QString::number(rowData[i]); // Convert double to QString
        labelText += ", "; // Add a comma and a space after each data element
    }
    labelText += (result ? "Y" : "N");
    if(result==false){
    labelText += "\n";


    }


    // Now rowData contains all the user input converted to doubles
    } catch (const std::invalid_argument& e) {
        // Handle the error (e.g., display an error message)
        qDebug() << "Error: " << e.what();
        }



    // Clear line edits for the next entry if needed
    ui->lineEdit1_3->clear();
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






