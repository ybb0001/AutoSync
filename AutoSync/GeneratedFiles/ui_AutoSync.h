/********************************************************************************
** Form generated from reading UI file 'AutoSync.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTOSYNC_H
#define UI_AUTOSYNC_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AutoSyncClass
{
public:
    QTextEdit *from;
    QLabel *label;
    QPushButton *pushButton_Manual;
    QTextBrowser *log;
    QLabel *label_2;
    QTextBrowser *textBrowser_files;
    QComboBox *comboBox;

    void setupUi(QWidget *AutoSyncClass)
    {
        if (AutoSyncClass->objectName().isEmpty())
            AutoSyncClass->setObjectName(QStringLiteral("AutoSyncClass"));
        AutoSyncClass->resize(450, 100);
        from = new QTextEdit(AutoSyncClass);
        from->setObjectName(QStringLiteral("from"));
        from->setGeometry(QRect(5, 25, 370, 35));
        label = new QLabel(AutoSyncClass);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(15, 5, 160, 16));
        pushButton_Manual = new QPushButton(AutoSyncClass);
        pushButton_Manual->setObjectName(QStringLiteral("pushButton_Manual"));
        pushButton_Manual->setGeometry(QRect(377, 30, 71, 31));
        log = new QTextBrowser(AutoSyncClass);
        log->setObjectName(QStringLiteral("log"));
        log->setGeometry(QRect(5, 65, 440, 400));
        label_2 = new QLabel(AutoSyncClass);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(285, 5, 95, 16));
        textBrowser_files = new QTextBrowser(AutoSyncClass);
        textBrowser_files->setObjectName(QStringLiteral("textBrowser_files"));
        textBrowser_files->setGeometry(QRect(385, 3, 51, 24));
        comboBox = new QComboBox(AutoSyncClass);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(190, 1, 80, 23));

        retranslateUi(AutoSyncClass);

        QMetaObject::connectSlotsByName(AutoSyncClass);
    } // setupUi

    void retranslateUi(QWidget *AutoSyncClass)
    {
        AutoSyncClass->setWindowTitle(QApplication::translate("AutoSyncClass", "AutoSync_241126", 0));
        from->setHtml(QApplication::translate("AutoSyncClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", 0));
        label->setText(QApplication::translate("AutoSyncClass", "Network Source Folder Path", 0));
        pushButton_Manual->setText(QApplication::translate("AutoSyncClass", "Sync \n"
" Start", 0));
        label_2->setText(QApplication::translate("AutoSyncClass", "Remaining Files: ", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("AutoSyncClass", "0", 0)
         << QApplication::translate("AutoSyncClass", "1", 0)
         << QApplication::translate("AutoSyncClass", "2", 0)
         << QApplication::translate("AutoSyncClass", "3", 0)
         << QApplication::translate("AutoSyncClass", "4", 0)
         << QApplication::translate("AutoSyncClass", "5", 0)
         << QApplication::translate("AutoSyncClass", "6", 0)
         << QApplication::translate("AutoSyncClass", "7", 0)
         << QApplication::translate("AutoSyncClass", "8", 0)
         << QApplication::translate("AutoSyncClass", "9", 0)
         << QApplication::translate("AutoSyncClass", "10", 0)
         << QApplication::translate("AutoSyncClass", "11", 0)
         << QApplication::translate("AutoSyncClass", "12", 0)
         << QApplication::translate("AutoSyncClass", "13", 0)
         << QApplication::translate("AutoSyncClass", "14", 0)
         << QApplication::translate("AutoSyncClass", "15", 0)
         << QApplication::translate("AutoSyncClass", "16", 0)
         << QApplication::translate("AutoSyncClass", "17", 0)
         << QApplication::translate("AutoSyncClass", "18", 0)
         << QApplication::translate("AutoSyncClass", "19", 0)
         << QApplication::translate("AutoSyncClass", "20", 0)
         << QApplication::translate("AutoSyncClass", "21", 0)
         << QApplication::translate("AutoSyncClass", "22", 0)
         << QApplication::translate("AutoSyncClass", "23", 0)
         << QApplication::translate("AutoSyncClass", "24", 0)
         << QApplication::translate("AutoSyncClass", "25", 0)
         << QApplication::translate("AutoSyncClass", "26", 0)
         << QApplication::translate("AutoSyncClass", "27", 0)
         << QApplication::translate("AutoSyncClass", "28", 0)
         << QApplication::translate("AutoSyncClass", "29", 0)
         << QApplication::translate("AutoSyncClass", "30", 0)
         << QApplication::translate("AutoSyncClass", "31", 0)
        );
    } // retranslateUi

};

namespace Ui {
    class AutoSyncClass: public Ui_AutoSyncClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTOSYNC_H
