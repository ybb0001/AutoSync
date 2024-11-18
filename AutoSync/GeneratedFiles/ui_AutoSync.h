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
        label->setGeometry(QRect(15, 5, 171, 16));
        pushButton_Manual = new QPushButton(AutoSyncClass);
        pushButton_Manual->setObjectName(QStringLiteral("pushButton_Manual"));
        pushButton_Manual->setGeometry(QRect(377, 30, 71, 31));
        log = new QTextBrowser(AutoSyncClass);
        log->setObjectName(QStringLiteral("log"));
        log->setGeometry(QRect(5, 65, 440, 300));
        label_2 = new QLabel(AutoSyncClass);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(280, 5, 101, 16));
        textBrowser_files = new QTextBrowser(AutoSyncClass);
        textBrowser_files->setObjectName(QStringLiteral("textBrowser_files"));
        textBrowser_files->setGeometry(QRect(385, 3, 51, 24));

        retranslateUi(AutoSyncClass);

        QMetaObject::connectSlotsByName(AutoSyncClass);
    } // setupUi

    void retranslateUi(QWidget *AutoSyncClass)
    {
        AutoSyncClass->setWindowTitle(QApplication::translate("AutoSyncClass", "AutoSync_241116", 0));
        from->setHtml(QApplication::translate("AutoSyncClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", 0));
        label->setText(QApplication::translate("AutoSyncClass", "Network Source Folder Path", 0));
        pushButton_Manual->setText(QApplication::translate("AutoSyncClass", "Sync \n"
" Start", 0));
        label_2->setText(QApplication::translate("AutoSyncClass", "Remaining Files: ", 0));
    } // retranslateUi

};

namespace Ui {
    class AutoSyncClass: public Ui_AutoSyncClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTOSYNC_H
