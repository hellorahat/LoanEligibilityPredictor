/********************************************************************************
** Form generated from reading UI file 'bulkeva.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BULKEVA_H
#define UI_BULKEVA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_Bulkeva
{
public:
    QPushButton *pushButton_OPENCSV;
    QLabel *label;
    QPushButton *pushButton_bulkeva;
    QPushButton *pushButton_export;
    QProgressBar *progressBar;
    QTextEdit *resultLabel;

    void setupUi(QDialog *Bulkeva)
    {
        if (Bulkeva->objectName().isEmpty())
            Bulkeva->setObjectName(QString::fromUtf8("Bulkeva"));
        Bulkeva->resize(407, 443);
        pushButton_OPENCSV = new QPushButton(Bulkeva);
        pushButton_OPENCSV->setObjectName(QString::fromUtf8("pushButton_OPENCSV"));
        pushButton_OPENCSV->setGeometry(QRect(80, 60, 211, 41));
        label = new QLabel(Bulkeva);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(110, 20, 141, 41));
        pushButton_bulkeva = new QPushButton(Bulkeva);
        pushButton_bulkeva->setObjectName(QString::fromUtf8("pushButton_bulkeva"));
        pushButton_bulkeva->setGeometry(QRect(80, 110, 211, 41));
        pushButton_export = new QPushButton(Bulkeva);
        pushButton_export->setObjectName(QString::fromUtf8("pushButton_export"));
        pushButton_export->setGeometry(QRect(90, 350, 211, 41));
        progressBar = new QProgressBar(Bulkeva);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(80, 160, 211, 21));
        progressBar->setValue(0);
        resultLabel = new QTextEdit(Bulkeva);
        resultLabel->setObjectName(QString::fromUtf8("resultLabel"));
        resultLabel->setGeometry(QRect(80, 190, 211, 141));

        retranslateUi(Bulkeva);

        QMetaObject::connectSlotsByName(Bulkeva);
    } // setupUi

    void retranslateUi(QDialog *Bulkeva)
    {
        Bulkeva->setWindowTitle(QCoreApplication::translate("Bulkeva", "Dialog", nullptr));
        pushButton_OPENCSV->setText(QCoreApplication::translate("Bulkeva", "Open CSV", nullptr));
        label->setText(QCoreApplication::translate("Bulkeva", "Bulk Evaluation", nullptr));
        pushButton_bulkeva->setText(QCoreApplication::translate("Bulkeva", "Evaluate", nullptr));
        pushButton_export->setText(QCoreApplication::translate("Bulkeva", "Export Evaluation", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Bulkeva: public Ui_Bulkeva {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BULKEVA_H
