/********************************************************************************
** Form generated from reading UI file 'load_data.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOAD_DATA_H
#define UI_LOAD_DATA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Load_Data
{
public:
    QLabel *label;
    QPushButton *Open_CSV;
    QPushButton *pushButton_2;

    void setupUi(QDialog *Load_Data)
    {
        if (Load_Data->objectName().isEmpty())
            Load_Data->setObjectName(QString::fromUtf8("Load_Data"));
        Load_Data->resize(519, 601);
        label = new QLabel(Load_Data);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(170, 20, 131, 61));
        QFont font;
        font.setPointSize(16);
        label->setFont(font);
        Open_CSV = new QPushButton(Load_Data);
        Open_CSV->setObjectName(QString::fromUtf8("Open_CSV"));
        Open_CSV->setGeometry(QRect(120, 140, 201, 91));
        pushButton_2 = new QPushButton(Load_Data);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(120, 280, 201, 91));

        retranslateUi(Load_Data);

        QMetaObject::connectSlotsByName(Load_Data);
    } // setupUi

    void retranslateUi(QDialog *Load_Data)
    {
        Load_Data->setWindowTitle(QCoreApplication::translate("Load_Data", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Load_Data", "Load Data", nullptr));
        Open_CSV->setText(QCoreApplication::translate("Load_Data", "Open CSV", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Load_Data", "Save Data", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Load_Data: public Ui_Load_Data {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOAD_DATA_H
