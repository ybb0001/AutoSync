#pragma once

#include <QtWidgets/QWidget>
#include "ui_AutoSync.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <direct.h>
#include <io.h>
#include <afx.h>
#include <QIcon>
#include <fstream>
#include <qdatetime.h>
#include <md5.h>
#include <QScreen>
#include <QDir>

using namespace std;

#ifdef UNICODE

#define QStringToTCHAR(x)     (wchar_t*) x.utf16()

#define PQStringToTCHAR(x)    (wchar_t*) x->utf16()

#define TCHARToQString(x)     QString::fromUtf16((x))

#define TCHARToQStringN(x,y)  QString::fromUtf16((x),(y))

#else

#define QStringToTCHAR(x)     x.local8Bit().constData()

#define PQStringToTCHAR(x)    x->local8Bit().constData()

#define TCHARToQString(x)     QString::fromLocal8Bit((x))

#define TCHARToQStringN(x,y)  QString::fromLocal8Bit((x),(y))

#endif

class AutoSync : public QWidget
{
	Q_OBJECT

public:
	AutoSync(QWidget *parent = Q_NULLPTR);

	void log_out(string src,int type = 0 );
	int get_Setting_MD5(string s);
	int MD5_check();
	bool path_Check(QString scan_path,int Path_level);
	bool path_Check2(QString scan_path, int Path_level);


private slots :
	void onAlgComboxSelect(int select);
	void on_pushButton_Manual_clicked();

private:
	Ui::AutoSyncClass ui;


};
