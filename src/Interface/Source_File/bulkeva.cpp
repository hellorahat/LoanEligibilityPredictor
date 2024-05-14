#include "../Header_File/bulkeva.h"
#include "ui_bulkeva.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>

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

std::vector<std::vector<std::string>> Bulkeva::readCSV(const QString& fileName)
{
    std::vector<std::vector<std::string>> csvData;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file: " << fileName;
        return csvData;
    }

    QTextStream in(&file);
    QString line = in.readLine(); // Read the entire line

    // Split the line by commas
    QStringList fields = line.split(",", Qt::SkipEmptyParts);

    // Calculate the number of sets of 13 variables
    int numSets = fields.size() / 13;

    // Check if the number of fields is divisible by 13
    if (fields.size() % 13 != 0) {
        qDebug() << "Invalid CSV format. Number of fields is not a multiple of 13.";
        file.close();
        return csvData;
    }

    // Process each set of 13 variables
    for (int i = 0; i < numSets; ++i) {
        std::vector<std::string> row;
        for (int j = 0; j < 13; ++j) {
            // Discard the first 13 fields (variables) in each set
            fields.pop_front();
        }
        // Process the remaining fields as data
        for (int j = 0; j < 13; ++j) {
            row.push_back(fields.front().toStdString());
            fields.pop_front();
        }
        csvData.push_back(row);
    }

    file.close();
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
        qDebug() << "No CSV data loaded. Please open a CSV file first.";
        return;
    }

    // Clear any existing data in the UI text edit widget
    ui->resultLabel->clear();

    int totalRows = csvData.size();
    int processedRows = 0;

    // Process the CSV data and update progress bar and result in real-time
    for (const auto& row : csvData) {
        // Process the current row (placeholder)
        bool result = true;

        // Append the CSV data row to the text edit widget along with the result
        QString rowText;
        for (const auto& field : row) {
            rowText.append(QString::fromStdString(field));
            rowText.append("\t"); // Add tab between fields
        }
        rowText.append(result ? "Y" : "N"); // Append the result to the row
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

