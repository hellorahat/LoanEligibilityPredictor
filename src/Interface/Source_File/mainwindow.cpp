#include "../Header_File/mainwindow.h"
#include "ui_mainwindow.h"
#include "../Header_File/load_data.h"
#include "../Header_File/evaluate_data.h"
#include <QFileDialog>
#include <QMessageBox>

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
    QString directory = QFileDialog::getExistingDirectory(this, tr("Select Directory"),
                                                          QDir::homePath(),
                                                          QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (!directory.isEmpty()) {
        // If a directory is selected, create the log file in that directory
        QString fileName = directory + "/log.txt";
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << "Log file created at: " << QDateTime::currentDateTime().toString() << "\n";
            out << "User selected directory: " << directory << "\n";
            out << "Additional information can be added here...\n";
            file.close();
            QMessageBox::information(this, tr("Success"), tr("Log file saved to %1").arg(fileName));
        } else {
            QMessageBox::critical(this, tr("Error"), tr("Failed to create log file."));
        }
    }
}