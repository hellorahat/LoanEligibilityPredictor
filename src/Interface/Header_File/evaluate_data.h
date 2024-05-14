#ifndef EVALUATE_DATA_H
#define EVALUATE_DATA_H

#include <QDialog>
#include "singleeva.h"
#include "bulkeva.h"

namespace Ui {
class Evaluate_Data;
}

class Evaluate_Data : public QDialog
{
    Q_OBJECT

public:
    explicit Evaluate_Data(QWidget *parent = nullptr);
    ~Evaluate_Data();

private slots:
    void on_Singleeva_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Evaluate_Data *ui;
};

#endif // EVALUATE_DATA_H
