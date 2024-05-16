#include "../Header_File/load_data.h"
#include "../Includes/DataFrame.h"
#include "../DataProcessing/DataHandler.h"
#include "../ui_load_data.h"
#include <QFileDialog>
#include <QTemporaryFile>


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

std::vector<std::vector<double>>Load_Data::readCSVV(const QString& fileName)
{
    std::vector<std::vector<double>>csvDataa;

    // Convert QFile to std::ifstream
    QFile training_data(fileName);
    if (!training_data.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file: " << fileName;
        return csvDataa;
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
    categorical_indexes.push_back(0);
    categorical_indexes.push_back(1);
    DataFrame *df = data_handler.process_data(fileStream, categorical_indexes);
    std::vector<std::string> feature_name_vec = df->get_feature_name_vec();// the header row: this contains the column names
    std::vector<std::vector<double>> double_vec = df->get_data_vec(); // the raw data content
    csvDataa = double_vec;


    tempFile.close();
    return csvDataa;
}


void Load_Data::on_Open_CSV_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open CSV File"),
                                                    "",
                                                    tr("CSV Files (*.csv);;All Files (*)"));

    if (!fileName.isEmpty()) {
        csvDataa = readCSVV(fileName);
        // You can optionally display the selected file name
        qDebug() << "Selected CSV file: " << fileName;
    }

    int totalRows = csvDataa.size();
    int processedRows = 0;
    int lineNumber = 1; // Counter for line numbers

        // Process the CSV data
        for (const auto& row : csvDataa) {
            // Process the current row (placeholder)
            // Update progress bar
            // call the random forest here with row
            processedRows++;
            int progress = static_cast<int>((processedRows / static_cast<double>(totalRows)) * 100);
            ui->progressBar->setValue(progress);



            // Force GUI update to show real-time changes
            QCoreApplication::processEvents();
        }
}
