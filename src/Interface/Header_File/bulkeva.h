#ifndef BULKEVA_H
#define BULKEVA_H

#include <QDialog>
#include "../../Includes/DataFrame.h"

namespace Ui {
class Bulkeva;
}

class Bulkeva : public QDialog
{
    Q_OBJECT

public:
    explicit Bulkeva(QWidget *parent = nullptr);
    ~Bulkeva();


private slots:
    //open CSV file
    void on_pushButton_OPENCSV_clicked();


    void on_pushButton_bulkeva_clicked();

    void on_pushButton_export_clicked();

private:
    Ui::Bulkeva *ui;
    std::vector<std::vector<double>>readCSV(const QString& fileName);
    std::vector<std::vector<double>>csvData;
    DataFrame *df;

};

#endif // BULKEVA_H
