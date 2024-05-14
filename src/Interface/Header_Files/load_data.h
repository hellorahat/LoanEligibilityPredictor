#ifndef LOAD_DATA_H
#define LOAD_DATA_H

#include <QDialog>

namespace Ui {
class load_data;
}

class load_data : public QDialog
{
    Q_OBJECT

public:
    explicit load_data(QWidget *parent = nullptr);
    ~load_data();

private slots:
    void on_pushButton_clicked();

private:
    Ui::load_data *ui;
    std::vector<std::vector<std::string>> readCSV(const QString& fileName);
};

#endif // LOAD_DATA_H
