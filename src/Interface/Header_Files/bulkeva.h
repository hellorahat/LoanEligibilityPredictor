#ifndef BULKEVA_H
#define BULKEVA_H

#include <QDialog>
#include <vector>
#include <string>

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
    std::vector<std::vector<std::string>> readCSV(const QString& fileName);
    std::vector<std::vector<std::string>> csvData;

};

#endif // BULKEVA_H
