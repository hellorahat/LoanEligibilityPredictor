#ifndef LOAD_DATA_H
#define LOAD_DATA_H

#include <QDialog>
#include <vector>
#include <string>

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
    std::vector<std::vector<std::string>> readCSV(const QString& fileName);
};

#endif // LOAD_DATA_H
