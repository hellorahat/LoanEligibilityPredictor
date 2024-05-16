#include "../Header_File/singleeva.h"
#include "../ui_singleeva.h"
#include "../../CoreLogic/SuggestionGenerator.h"
#include <QDebug>
#include <QTemporaryFile>
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
    QString credit_policy_0 = ui->lineEdit->text();
    QString credit_policy_1 = ui->lineEdit_2->text();
    QString purpose_educational = ui->lineEdit_3->text();
    QString purpose_major_purchase = ui->lineEdit_4->text();
    QString purpose_small_business = ui->lineEdit_5->text();
    QString purpose_home_improvement = ui->lineEdit_6->text();
    QString purpose_all_other = ui->lineEdit_7->text();
    QString purpose_credit_card = ui->lineEdit_8->text();
    QString purpose_debt_consolidation = ui->lineEdit_9->text();
    QString interest_rate = ui->lineEdit_10->text();
    QString installment = ui->lineEdit_11->text();
    QString log_annual_income = ui->lineEdit_12->text();
    QString debt_to_income = ui->lineEdit_13->text();
    QString fico_score = ui->lineEdit_14->text();
    QString days_with_credit_line = ui->lineEdit_15->text();
    QString revolving_balance = ui->lineEdit_16->text();
    QString revolving_utilization_rate = ui->lineEdit_17->text();
    QString inquiries_last_6_months = ui->lineEdit_18->text();
    QString past_due_last_2_years = ui->lineEdit_19->text();
    QString derogatory_public_records = ui->lineEdit_20->text();
    QString not_fully_paid = ui->lineEdit_21->text();

    // Convert QString values to doubles and store in vector<double>
    std::vector<double> rowData = {
        convertToDouble(credit_policy_0),
        convertToDouble(credit_policy_1),
        convertToDouble(purpose_educational),
        convertToDouble(purpose_major_purchase),
        convertToDouble(purpose_small_business),
        convertToDouble(purpose_home_improvement),
        convertToDouble(purpose_all_other),
        convertToDouble(purpose_credit_card),
        convertToDouble(purpose_debt_consolidation),
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

        //output the data input by user into a file to call SuggenstionGenerator
    //qDebug() << "Make temFile: ";
        QTemporaryFile sinFile;
        sinFile.open(); // Open the temporary file
        QDataStream out(&sinFile);
        out << static_cast<quint32>(rowData.size());
        for (const double& value : rowData) {
            out << value;
        }
    //qDebug() << "temFile Finished";



    //qDebug() << "Call RandomForest: ";
        //call RandomForest
        //RandomForest forest(3);
        //int result = forest.predict(rowData);
    int result = 0; // dummy function to test
    QString ResultLabel = "Data: ";
    for (size_t i = 0; i < rowData.size(); ++i) {
        ResultLabel += QString::number(rowData[i]); // Convert double to QString
        ResultLabel += ", "; // Add a comma and a space after each data element
    }
    if (result == 0) {
        ResultLabel.append("Y"); // Append the result to the row
    } else {
        ResultLabel.append("N"); // Append the result to the row
        ResultLabel.append("\n");
        SuggestionGenerator sg = SuggestionGenerator();
        std::vector<double>closest_vec=sg.get_closest_positive_prediction(rowData,fd);
        ResultLabel.append("Closest vector: ");
        for (size_t i = 0; i < closest_vec.size(); ++i) {
            ResultLabel.append(QString::number(closest_vec[i]));
            if (i < closest_vec.size() - 1)
                ResultLabel.append(", "); // Add comma and space between elements
        }
    }
    ui->ResultLabel->setText(ResultLabel);





    // Now rowData contains all the user input converted to doubles
    } catch (const std::invalid_argument& e) {
        // Handle the error (e.g., display an error message)
        qDebug() << "Error: " << e.what();
        }



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
        ui->lineEdit_15->clear();
        ui->lineEdit_16->clear();
        ui->lineEdit_17->clear();
        ui->lineEdit_18->clear();
        ui->lineEdit_19->clear();
        ui->lineEdit_20->clear();
        ui->lineEdit_21->clear();
}



