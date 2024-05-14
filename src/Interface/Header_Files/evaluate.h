#ifndef EVALUATE_H
#define EVALUATE_H

#include <QDialog>

namespace Ui {
class evaluate;
}

class evaluate : public QDialog
{
    Q_OBJECT

public:
    explicit evaluate(QWidget *parent = nullptr);
    ~evaluate();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::evaluate *ui;
};

#endif // EVALUATE_H
