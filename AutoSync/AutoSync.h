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

class AutoSync : public QWidget
{
	Q_OBJECT

public:
	AutoSync(QWidget *parent = Q_NULLPTR);

	void log_out(string src,int type = 0 );
	int get_Setting_MD5(string s);
	int MD5_check();
	bool path_Check(QString scan_path,int Path_level);


private slots :

	void on_pushButton_Manual_clicked();

private:
	Ui::AutoSyncClass ui;


};
