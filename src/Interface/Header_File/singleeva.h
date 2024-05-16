#ifndef SINGLEEVA_H
#define SINGLEEVA_H

#include <QDialog>
"../../Includes/DataFrame.h"


namespace Ui {
class Singleeva;
}

class Singleeva : public QDialog
{
    Q_OBJECT

public:
    explicit Singleeva(QWidget *parent = nullptr);
    ~Singleeva();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Singleeva *ui;
    DataFrame *source_dataframe;
    //std::vector<std::vector<std::string>> data;
};

#endif // SINGLEEVA_H
