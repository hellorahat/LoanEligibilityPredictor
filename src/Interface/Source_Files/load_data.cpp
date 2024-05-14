#include "load_data.h"
#include "ui_load_data.h"
#include <QFileDialog>

load_data::load_data(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::load_data)
{
    ui->setupUi(this);
}

load_data::~load_data()
{
    delete ui;
}

std::vector<std::vector<std::string>> load_data::readCSV(const QString& fileName)
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

void load_data::on_pushButton_clicked()
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

