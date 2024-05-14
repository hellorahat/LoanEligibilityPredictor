#ifndef BULK_H
#define BULK_H

#include <QDialog>

namespace Ui {
class bulk;
}

class bulk : public QDialog
{
    Q_OBJECT

public:
    explicit bulk(QWidget *parent = nullptr);
    ~bulk();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::bulk *ui;
    std::vector<std::vector<std::string>> readCSV(const QString& fileName);
    std::vector<std::vector<std::string>> csvData;
};

#endif // BULK_H
