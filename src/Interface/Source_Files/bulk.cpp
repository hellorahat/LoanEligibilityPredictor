#include "bulk.h"
#include "ui_bulk.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>

bulk::bulk(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::bulk)
{
    ui->setupUi(this);
}

bulk::~bulk()
{
    delete ui;
}

std::vector<std::vector<std::string>> bulk::readCSV(const QString& fileName)
{
    std::vector<std::vector<std::string>> csvData;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file: " << fileName;
        return csvData;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",", Qt::SkipEmptyParts);

        std::vector<std::string> row;
        for (const QString& field : fields) {
            row.push_back(field.toStdString());
        }
        csvData.push_back(row);
    }

    file.close();
    return csvData;
}

void bulk::on_pushButton_clicked()
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


void bulk::on_pushButton_2_clicked()
{
    if (csvData.empty()) {
        qDebug() << "No CSV data loaded. Please open a CSV file first.";
        return;
    }

    // Clear any existing data in the UI text edit widget
    ui->resultLable->clear();

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
        ui->resultLable->append(rowText);


        // Update progress bar
        processedRows++;
        int progress = static_cast<int>((processedRows / static_cast<double>(totalRows)) * 100);
        ui->progressBar->setValue(progress);


        // Force GUI update to show real-time changes
        QCoreApplication::processEvents();
    }
}


void bulk::on_pushButton_3_clicked()
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
                out << ui->resultLable->toPlainText();
                outputFile.close();
                qDebug() << "Output saved to file: " << fileName;
            } else {
                qDebug() << "Failed to open output file for writing: " << fileName;
            }
        }
    }
}

