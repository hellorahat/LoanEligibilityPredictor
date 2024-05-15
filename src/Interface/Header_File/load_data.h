#ifndef LOAD_DATA_H
#define LOAD_DATA_H

#include <QDialog>

namespace Ui {
class Load_Data;
}

class Load_Data : public QDialog
{
    Q_OBJECT

public:
    explicit Load_Data(QWidget *parent = nullptr);
    ~Load_Data();

private slots:
    void on_Open_CSV_clicked();

private:
    Ui::Load_Data *ui;
    std::vector<std::vector<double>>readCSVV(const QString& fileName);
    std::vector<std::vector<double>>csvDataa;
};

#endif // LOAD_DATA_H
