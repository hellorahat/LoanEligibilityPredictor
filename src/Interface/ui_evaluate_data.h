/********************************************************************************
** Form generated from reading UI file 'evaluate_data.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EVALUATE_DATA_H
#define UI_EVALUATE_DATA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Evaluate_Data
{
public:
    QPushButton *Singleeva;
    QPushButton *pushButton_2;
    QLabel *label;

    void setupUi(QDialog *Evaluate_Data)
    {
        if (Evaluate_Data->objectName().isEmpty())
            Evaluate_Data->setObjectName(QString::fromUtf8("Evaluate_Data"));
        Evaluate_Data->resize(486, 549);
        Singleeva = new QPushButton(Evaluate_Data);
        Singleeva->setObjectName(QString::fromUtf8("Singleeva"));
        Singleeva->setGeometry(QRect(140, 130, 181, 81));
        pushButton_2 = new QPushButton(Evaluate_Data);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(140, 260, 181, 81));
        label = new QLabel(Evaluate_Data);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(170, 40, 131, 61));

        retranslateUi(Evaluate_Data);

        QMetaObject::connectSlotsByName(Evaluate_Data);
    } // setupUi

    void retranslateUi(QDialog *Evaluate_Data)
    {
        Evaluate_Data->setWindowTitle(QCoreApplication::translate("Evaluate_Data", "Dialog", nullptr));
        Singleeva->setText(QCoreApplication::translate("Evaluate_Data", "Single evaluation", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Evaluate_Data", "Bulk Evaluation", nullptr));
        label->setText(QCoreApplication::translate("Evaluate_Data", "Evaluate Data", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Evaluate_Data: public Ui_Evaluate_Data {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EVALUATE_DATA_H
