#include "../Header_File/bulkeva.h"
#include "../ui_bulkeva.h"
#include "../../Includes/DataFrame.h"
#include "../../DataProcessing/DataHandler.h"
#include "../../CoreLogic/SuggestionGenerator.h"
#include "../../CoreLogic/RandomForest.h"
#include "../../CoreLogic/DecisionTree.h"
#include "../../CoreLogic/Node.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QTemporaryFile>
#include <QMessageBox>

Bulkeva::Bulkeva(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Bulkeva)
{
    ui->setupUi(this);

}

Bulkeva::~Bulkeva()
{
    delete ui;
}

std::vector<std::vector<double>>Bulkeva::readCSV(const QString& fileName)
{
    std::vector<std::vector<double>>csvData;

    // Convert QFile to std::ifstream
    QFile training_data(fileName);
    if (!training_data.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file: " << fileName;
        return csvData;
    }

    QTemporaryFile tempFile;
    tempFile.setAutoRemove(true); // This ensures that the temporary file is deleted automatically when it's no longer needed
    if (tempFile.open()) {
        // Write the contents of the QFile to the temporary file
        tempFile.write(training_data.readAll());
        // Seek back to the beginning of the file
        tempFile.seek(0);
    }
    std::ifstream fileStream(tempFile.fileName().toStdString());

    // Call the data processor
    DataHandler data_handler;
    std::vector<int> categorical_indexes = {0,1};
    df = data_handler.process_data(fileStream, categorical_indexes);
    std::vector<std::string> feature_name_vec = df->get_feature_name_vec();// the header row: this contains the column names
    std::vector<std::vector<double>> double_vec = df->get_data_vec(); // the raw data content
    csvData = double_vec;

    return csvData;
}

// open file
void Bulkeva::on_pushButton_OPENCSV_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open CSV File"),
                                                    "",
                                                    tr("CSV Files (*.csv);;All Files (*)"));

    if (!fileName.isEmpty()) {
        csvData = readCSV(fileName);
        // You can optionally display the selected file name
        qDebug() << "Selected CSV file: " << fileName;
    }
}

// Process CSV file and update progress bar and result
void Bulkeva::on_pushButton_bulkeva_clicked()
{
    if (csvData.empty()) {
        QMessageBox::warning(this, "No CSV Data", "No CSV data loaded. Please open a CSV file first.");
        return;
    }

    // Clear any existing data in the UI text edit widget
    ui->resultLabel->clear();

    int totalRows = csvData.size();
    int processedRows = 0;
    int lineNumber = 1; // Counter for line numbers


    RandomForest forest(3);

    // Process the CSV data and update progress bar and result in real-time
    for (const auto& row : csvData) {
        // Convert the row data to vector<double> to pass to the predict function
        std::vector<double> features;
        for (const auto& field : row) {
            features.push_back(field);
        }

        // Call the predict function with the features
        //int result = forest.predict(features);
        int result = 0;
        // Append the CSV data row to the text edit widget along with the result
        QString rowText = QString::number(lineNumber++) + ","; // Add line number
        for (const auto& field : row) {
            rowText.append(QString::number(field)); // Convert double to QString
            rowText.append(","); // Add tab between fields
        }
        if (result == 0) {
            rowText.append("Y"); // Append the result to the row
        } else {
            rowText.append("N"); // Append the result to the row
            rowText.append("\n");
            SuggestionGenerator sg = SuggestionGenerator();
            std::vector<double>closest_vec=sg.get_closest_positive_prediction(row,df);
            rowText.append("Closest vector: ");
            for (size_t i = 0; i < closest_vec.size(); ++i) {
                rowText.append(QString::number(closest_vec[i]));
                if (i < closest_vec.size() - 1)
                    rowText.append(", "); // Add comma and space between elements
            }
        }
        rowText.append("\n"); // Add a newline after each row
        ui->resultLabel->append(rowText);


        // Update progress bar
        processedRows++;
        int progress = static_cast<int>((processedRows / static_cast<double>(totalRows)) * 100);
        ui->progressBar->setValue(progress);


        // Force GUI update to show real-time changes
        QCoreApplication::processEvents();
    }
}

//Export Evaluation
void Bulkeva::on_pushButton_export_clicked()
{
    {
        QString fileName = QFileDialog::getSaveFileName(this,
                                                        tr("Save Output File"),
                                                        "",
                                                        tr("Text Files (*.txt);;All Files (*)"));

        if (!fileName.isEmpty()) {
            QFile outputFile(fileName);
            if (outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream out(&outputFile);
                out << ui->resultLabel->toPlainText();
                outputFile.close();
                qDebug() << "Output saved to file: " << fileName;
            } else {
                qDebug() << "Failed to open output file for writing: " << fileName;
            }
        }
    }
}

