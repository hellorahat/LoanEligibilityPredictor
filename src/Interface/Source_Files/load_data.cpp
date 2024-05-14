#include "../Header_Files/load_data.h"
#include "ui_load_data.h"
#include <QFileDialog>

Load_Data::Load_Data(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Load_Data)
{
    ui->setupUi(this);

}

Load_Data::~Load_Data()
{
    delete ui;
}

std::vector<std::vector<std::string>> Load_Data::readCSV(const QString& fileName)
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


void Load_Data::on_Open_CSV_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open CSV File"),
                                                    "",
                                                    tr("CSV Files (*.csv);;All Files (*)"));

    if (!fileName.isEmpty()) {
        std::vector<std::vector<std::string>> csvData = readCSV(fileName);
        int totalRows = csvData.size();
        int processedRows = 0;

        // Process the CSV data
        for (const auto& row : csvData) {
            // Process the current row (placeholder)



            // Force GUI update to show real-time changes
            QCoreApplication::processEvents();
        }
    }
}

