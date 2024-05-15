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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Bulkeva
{
public:
    QLabel *label;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_OPENCSV;
    QPushButton *pushButton_bulkeva;
    QProgressBar *progressBar;
    QTextEdit *resultLabel;
    QPushButton *pushButton_export;

    void setupUi(QDialog *Bulkeva)
    {
        if (Bulkeva->objectName().isEmpty())
            Bulkeva->setObjectName(QString::fromUtf8("Bulkeva"));
        Bulkeva->resize(1337, 886);
        label = new QLabel(Bulkeva);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(470, 10, 351, 71));
        widget = new QWidget(Bulkeva);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(200, 140, 931, 681));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_OPENCSV = new QPushButton(widget);
        pushButton_OPENCSV->setObjectName(QString::fromUtf8("pushButton_OPENCSV"));

        verticalLayout->addWidget(pushButton_OPENCSV);

        pushButton_bulkeva = new QPushButton(widget);
        pushButton_bulkeva->setObjectName(QString::fromUtf8("pushButton_bulkeva"));

        verticalLayout->addWidget(pushButton_bulkeva);

        progressBar = new QProgressBar(widget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(0);

        verticalLayout->addWidget(progressBar);

        resultLabel = new QTextEdit(widget);
        resultLabel->setObjectName(QString::fromUtf8("resultLabel"));

        verticalLayout->addWidget(resultLabel);

        pushButton_export = new QPushButton(widget);
        pushButton_export->setObjectName(QString::fromUtf8("pushButton_export"));

        verticalLayout->addWidget(pushButton_export);


        retranslateUi(Bulkeva);

        QMetaObject::connectSlotsByName(Bulkeva);
    } // setupUi

    void retranslateUi(QDialog *Bulkeva)
    {
        Bulkeva->setWindowTitle(QCoreApplication::translate("Bulkeva", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Bulkeva", "Bulk Evaluation", nullptr));
        pushButton_OPENCSV->setText(QCoreApplication::translate("Bulkeva", "Open CSV", nullptr));
        pushButton_bulkeva->setText(QCoreApplication::translate("Bulkeva", "Evaluate", nullptr));
        pushButton_export->setText(QCoreApplication::translate("Bulkeva", "Export Evaluation", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Bulkeva: public Ui_Bulkeva {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BULKEVA_H
