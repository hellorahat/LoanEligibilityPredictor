#ifndef SINGLE_H
#define SINGLE_H

#include <QDialog>

namespace Ui {
class single;
}

class single : public QDialog
{
    Q_OBJECT

public:
    explicit single(QWidget *parent = nullptr);
    ~single();

private slots:
    void on_pushButton_clicked();

private:
    Ui::single *ui;
};

#endif // SINGLE_H
