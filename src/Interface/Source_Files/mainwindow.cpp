#include "../Header_Files/mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// open load data page by click load data
void MainWindow::on_pushButton_clicked()
{
    Load_Data loaddata;
    loaddata.setModal(true);
    loaddata.exec();
}

// open evaluate data page by click evaluate data
void MainWindow::on_pushButton_2_clicked()
{
    Evaluate_Data evadata;
    evadata.setModal(true);
    evadata.exec();
}

void MainWindow::on_LogFile_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save Log File"),
                                                    "",
                                                    tr("Text files (*.txt);;All files (*)"));

    if (!fileName.isEmpty()) {
        QFile logFile(fileName);
        if (!logFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "Failed to open log file for writing.";
            return;
        }

        QTextStream out(&logFile);
        out << "Log data goes here.\n";

        logFile.close();

        qDebug() << "Log file generated successfully at" << fileName;
    }
}

