#include "AutoSync.h"

string del_Path_Words[3] = { "temp","log","mes" };
string src[32] = { "" }, dst = "" , del_path = "";
string Exe_Path[5] = { "","","","","" };

string upper_src = "", upper_src2 = "", upper_src3 = "";
string setting_copy = "", setting_MD5 = "", setting2 = "", setting3 = "";
LPCWSTR Lsetting = TEXT("");
HANDLE myHandle;

string skip_Words_MD5[32] = { "" };
string special_Path[16] = { "" };
string keep_Path[16] = { "" };
string keep_Type[16] = { "" };

int keep_cnt[16] = { 0 };
string keep_Words[16][256] = { "" };
string keep_Temp[256] = { "" };

string base_path[8192] = { "" };
string file_hash[8192] = { "" };
string root_path[1024] = { "" };
string empty_path[1024] = { "" };

string pw = "";
int use_Data[1024] = { 0 };
bool start = true;
bool manual = false;
int mode = 1, exe_cnt = 0, sIndex = 0;
int copy_hour = 0, copy_minute = 0;
int database_cnt = 0, database_rest =0, root_cnt = 0, empty_cnt = 0;
bool ok = true;

//#define mLog_Print_On

#ifdef mLog_Print_On
ofstream fout("test_log.txt");
#endif

vector<string> getFiles(string cate_dir)
{
	vector<string> files;//存放文件名
	_finddata_t file;
	intptr_t lf = 0;

	if ((lf = _findfirst(cate_dir.c_str(), &file)) == -1) {
		//cout << cate_dir << " not found!!!" << endl;
	}
	else {
		while (_findnext(lf, &file) == 0) {
			//输出文件名
			//cout<<file.name<<endl;
			if (strcmp(file.name, ".") == 0 || strcmp(file.name, "..") == 0)
				continue;
			files.push_back(file.name);
		}
	}
	_findclose(lf);
	//sort(files.begin(), files.end());
	return files;
}

void path_Delete(string path) {

	vector<string> files = getFiles(path + "*.*");
	vector<string> ::iterator iVector = files.begin();
	while (iVector != files.end())
	{
		string s = path + *iVector;
		DeleteFile(CA2CT(s.c_str()));
		++iVector;
	}

}

int AutoSync::get_Setting_MD5(string s) {

	//if (_access(s.c_str(), 0)) {
		int ret =CopyFile(CA2CT(setting3.c_str()), CA2CT(s.c_str()), false);
	//}
	if (ret!=1) {
		return 1;
	}

	if (_access(s.c_str(), 0)) {
		return 1;
	}

	TCHAR lpTexts[1024];
	for (int i = 0; i < 32; i++) {
		string t_str = "skip_filename_Words_" + to_string(i + 1);
		GetPrivateProfileString(TEXT("Scan_Setting"), CA2CT(t_str.c_str()), TEXT(""), lpTexts, 1024, CA2CT(s.c_str()));
		skip_Words_MD5[i] = CT2A(lpTexts);
	}

	for (int i = 0; i < 16; i++) {
		string t_str = "special_path_" + to_string(i + 1);
		GetPrivateProfileString(TEXT("Scan_Setting"), CA2CT(t_str.c_str()), TEXT(""), lpTexts, 1024, CA2CT(s.c_str()));
		special_Path[i] = CT2A(lpTexts);
	}
	//special_Path[9] = "current.atm";

	for (int i = 0; i < 16; i++) {
		string t_str = "file_path_" + to_string(i + 1);
		GetPrivateProfileString(TEXT("Keep_Path"), CA2CT(t_str.c_str()), TEXT(""), lpTexts, 1024, CA2CT(s.c_str()));
		keep_Path[i] = CT2A(lpTexts);
	}

	for (int i = 0; i < 16; i++) {
		if (keep_Path[i].length()>2) {
			string item_str = "keep_path_" + to_string(i + 1) + "_Type";
			GetPrivateProfileString(TEXT("Keep_Path"), CA2CT(item_str.c_str()), TEXT(""), lpTexts, 1024, CA2CT(s.c_str()));
			keep_Type[i] = CT2A(lpTexts);
			item_str = "keep_path_" + to_string(i + 1) + "_cnt";
			keep_cnt[i] = GetPrivateProfileInt(_T("Keep_Path"), CA2CT(item_str.c_str()), 0, CA2CT(s.c_str()));
			for (int j = 0; j < keep_cnt[i]; j++) {
				string words_str = "keep_path_" + to_string(i + 1) + "_words_"+ to_string(j + 1);
				GetPrivateProfileString(TEXT("Keep_Path"), CA2CT(words_str.c_str()), TEXT(""), lpTexts, 1024, CA2CT(s.c_str()));
				keep_Words[i][j] = CT2A(lpTexts);
			}
		}
	}

	root_cnt = GetPrivateProfileInt(_T("Root_Path"), TEXT("Datebase_Size"), 0, CA2CT(s.c_str()));
	empty_cnt = GetPrivateProfileInt(_T("Empty_Path"), TEXT("Datebase_Size"), 0, CA2CT(s.c_str()));

	for (int i = 0; i < root_cnt; i++) {
		string t_str = "folder_path" + to_string(i);
		GetPrivateProfileString(TEXT("Root_Path"), CA2CT(t_str.c_str()), TEXT(""), lpTexts, 1024, CA2CT(s.c_str()));
		root_path[i] = CT2A(lpTexts);
	}

	for (int i = 0; i < empty_cnt; i++) {
		string t_str = "folder_path" + to_string(i);
		GetPrivateProfileString(TEXT("Empty_Path"), CA2CT(t_str.c_str()), TEXT(""), lpTexts, 1024, CA2CT(s.c_str()));
		empty_path[i] = CT2A(lpTexts);
	}

	GetPrivateProfileString(TEXT("Scan_Setting"), TEXT("pw"), TEXT(""), lpTexts, 16, CA2CT(s.c_str()));
	pw = CT2A(lpTexts);

	database_cnt = GetPrivateProfileInt(_T("Scan_Setting"), TEXT("Datebase_Size"), 0, CA2CT(s.c_str()));
	database_rest = database_cnt;
	for (int i = 0; i < database_cnt; i++) {

		string a = "base_path" + to_string(i);
		GetPrivateProfileString(TEXT("Database_Path"), CA2CT(a.c_str()), TEXT(""), lpTexts, 1024, CA2CT(s.c_str()));
		base_path[i] = CT2A(lpTexts);

		a = "file_hash" + to_string(i);
		GetPrivateProfileString(TEXT("Database_MD5"), CA2CT(a.c_str()), TEXT(""), lpTexts, 1024, CA2CT(s.c_str()));
		file_hash[i] = CT2A(lpTexts);

		log_out(base_path[i]+ ":	"+ file_hash[i].c_str());
	}

	return 0;
}

bool capital_samll_check(char a, char b) {

	if (a == b)
		return true;
	if (a<96 && a + 32 == b)
		return true;
	if (a>96 && a - 32 == b)
		return true;

	return false;
}

int File_Name_Compare_Root(string file) {
#ifdef mLog_Print_On
	fout << "Root Compare: " << file << endl;
#endif
	int ret = -1;
	for (int k = 0; k < 32; k++) {
		if (root_path[k].length()>2) {
			int e = 0;
			while (e < root_path[k].length() && e < file.length() && file[e] == root_path[k][e]) {
				e++;
			}
			if (e == root_path[k].length() && e == file.length())
				return 99;

			if (file.length() > 12 && e >= root_path[k].length() - 6)
				return k;
		}
	}
	return ret;
}

bool File_Name_Compare_MD5(string file) {

#ifdef mLog_Print_On
	fout << "MD5 Compare: " << file << endl;
#endif

	for (int k = 0; k < 32; k++) {
		if (skip_Words_MD5[k].length()>2) {
			for (int i = 0; i < file.length(); i++) {
				if (file[i] == skip_Words_MD5[k][0]) {
					int e = 0;
					while (e < skip_Words_MD5[k].length() && i + e <file.length() && file[i + e] == skip_Words_MD5[k][e]) {
						e++;
					}
					if (e == skip_Words_MD5[k].length())
						return true;
				}
			}
		}
	}
	return false;
}

int checkPath(const std::string strPath)
{
	struct stat         infos;

	if (stat(strPath.c_str(), &infos) != 0)
	{
		return -1;    //无效
	}
	else if (infos.st_mode & S_IFDIR)
	{
		return 0;    //目录
	}
	else if (infos.st_mode & S_IFREG)
	{
		//这里多写一个if 是为了记录一下判断条件
		return 1;    //文件
	}
	else
	{
		return -1;
	}
}

string FileDigest(const string &file) {

	ifstream in(file.c_str(), ios::binary);
	if (!in)
		return "";

	MD5 md5;
	std::streamsize length;
	char buffer[1024];
	while (!in.eof()) {
		in.read(buffer, 1024);
		length = in.gcount();
		if (length > 0)
			md5.update(buffer, length);
	}
	in.close();
	return md5.toString();
}

int Speical_check(string file) {

	int ret = -1;
	for (int k = 0; k < 16; k++) {
		if (special_Path[k].length()>2) {
			for (int i = 0; i < file.length(); i++) {
				if (file[i] == special_Path[k][0]) {
					int e = 0;
					while (e < special_Path[k].length() && file[i + e] == special_Path[k][e]) {
						e++;
					}
					if (e == special_Path[k].length()&& e== file.length())
						return k;
				}
				else break;
			}
		}
	}

	for (int k = 0; k < 16; k++) {
		if (keep_Path[k].length()>2) {
			for (int i = 0; i < file.length(); i++) {
				if (file[i] == keep_Path[k][0]) {
					int e = 0;
					while (e < keep_Path[k].length() && file[i + e] == keep_Path[k][e]) {
						e++;
					}
					if (e == keep_Path[k].length() && e == file.length())
						return 100+k;
				}
				else break;
			}
		}
	}

	return ret;
}

bool AutoSync::path_Check(QString scan_path,int Path_level) {

	string s = scan_path.toStdString();
#ifdef mLog_Print_On
	fout << "Scan Path: " << s  << endl;
#endif
	vector<string> files1 = getFiles(s + "*.*");
#ifdef mLog_Print_On
	fout << " Files count: " << files1.size() << endl;
#endif
	vector<string> ::iterator iVector = files1.begin();
	int x = 0, ret = 0; bool folder_name = false;

	while (iVector != files1.end())
	{
		if (!File_Name_Compare_MD5(*iVector)) {
			string s_tail = s + *iVector;
			int root_result = File_Name_Compare_Root(*iVector);
			if (Path_level == 0 && root_result !=99) {
				string movePath = "..\\old_SW\\" + *iVector;
				if (root_result >= 0) {
					QString oldPath(s_tail.c_str());
					QDir dirOld(oldPath);
					string nPath=s + root_path[root_result];
					QString newPath((s + root_path[root_result]).c_str());

					for (int i = 0; i < 10; i++) {
						bool dret = dirOld.rename(oldPath, newPath);
						if (dret) {
							break;
						}
						else {
							Sleep(1000);
						}
					}
					for (int i = 0; i < 150; i++) {
						Sleep(100);
						if (_access(nPath.c_str(), 0)==0) {
							break;
						}
					}
					ret += path_Check(scan_path, 0);
					break;
				}		
			}
			else {

				if (checkPath(s + *iVector) == 1) {
					string s2 = src[sIndex] + s_tail.substr(3);
					string d2 = dst + s_tail.substr(3);
					int m_index = Speical_check(*iVector);
					string m = FileDigest(s_tail);
					string current1 = s_tail + "1";

					if (m_index != -1) {
						if (m_index <100) {
							if (_access(d2.c_str(), 0)) {
								CopyFile(CA2CT(s2.c_str()), CA2CT(d2.c_str()), false);
							}
						}
						else {
							if (_access(current1.c_str(), 0)) {
								m_index += 1000;
								CopyFile(CA2CT(s2.c_str()), CA2CT(current1.c_str()), false);
							}
							m = FileDigest(current1);
						}
					}

					bool noUse = true;
					string usPath = *iVector;
					int len = usPath.length();

					for (int i = 0; i < database_cnt; i++) {
						if (use_Data[i] == 0 && strcmp(base_path[i].c_str(), (s + *iVector).c_str()) == 0) {
							noUse = false;
							if (strcmp(file_hash[i].c_str(), m.c_str()) != 0) {
								if (m_index == -1|| (m_index >99&& m_index<1000)) {
									ret++;
									log_out(base_path[i] + ":	" + m, 1);
								}
								if (m_index > 99) {
									int c_ret = CopyFile(CA2CT(s2.c_str()), CA2CT(current1.c_str()), false);
									if (!c_ret) {
										DeleteFile(CA2CT(current1.c_str()));
										CopyFile(CA2CT(s2.c_str()), CA2CT(current1.c_str()), false);
									}
								}
								if (m_index == -1) {
									int c_ret = CopyFile(CA2CT(s2.c_str()), CA2CT(d2.c_str()), false);
									if (!c_ret) {
										DeleteFile(CA2CT(d2.c_str()));
										CopyFile(CA2CT(s2.c_str()), CA2CT(d2.c_str()), false);
									}
								}
							}

							if (m_index >99) {
								TCHAR lpTexts[1024];
								int r_index = m_index % 100;
								for (int k = 0; k < keep_cnt[r_index]; k++) {								
									GetPrivateProfileString(CA2CT(keep_Type[r_index].c_str()), CA2CT(keep_Words[r_index][k].c_str()), TEXT(""), lpTexts, 1024, CA2CT(d2.c_str()));
									keep_Temp[k] = CT2A(lpTexts);
									//LPWSTR keep_item = GetPrivateProfileInt(_T("SET_SERIAL_PORT"), TEXT("PORTCOMNUM"), 0, CA2CT(d2.c_str()));
									//LPWSTR keep_item = GetPrivateProfileString(_T("SET_SERIAL_PORT"), TEXT("PORTCOMNUM"), 0, CA2CT(d2.c_str()));
									//int PORTCOMNUM = GetPrivateProfileInt(_T("SET_SERIAL_PORT"), TEXT("PORTCOMNUM"), 0, CA2CT(d2.c_str()));
									//int PORT_BAUDS = GetPrivateProfileInt(_T("SET_SERIAL_PORT"), TEXT("PORT_BAUDS"), 0, CA2CT(d2.c_str()));
									//int c_ret = CopyFile(CA2CT(current1.c_str()), CA2CT(d2.c_str()), false);
									//WritePrivateProfileString(TEXT("SET_SERIAL_PORT"), TEXT("PORTCOMNUM"), CA2CT(to_string(PORTCOMNUM).c_str()), CA2CT(d2.c_str()));
									//WritePrivateProfileString(TEXT("SET_SERIAL_PORT"), TEXT("PORT_BAUDS"), CA2CT(to_string(PORT_BAUDS).c_str()), CA2CT(d2.c_str()));
								}
								int c_ret = CopyFile(CA2CT(current1.c_str()), CA2CT(d2.c_str()), false);
								for (int k = 0; k < keep_cnt[r_index]; k++) {
									WritePrivateProfileString(CA2CT(keep_Type[r_index].c_str()), CA2CT(keep_Words[r_index][k].c_str()), CA2CT(keep_Temp[k].c_str()), CA2CT(d2.c_str()));
								}
							}
							use_Data[i] = 1;
							ui.textBrowser_files->setText(to_string(--database_rest).c_str());
							repaint();

							if (Path_level % 10 == 1 && files1.size() > 30) {
								if (usPath[len - 1] == 'e'&&usPath[len - 2] == 'x'&&usPath[len - 3] == 'e'&&usPath[len - 4] == '.') {
									x++;
									if (x > 1) {
										log_out("more than 1ea exe files in this fold: " + s, 1);
										ret++;
									}
									else {
										Exe_Path[exe_cnt++] = s + *iVector;
									}
								}
							}
							break;
						}
					}

					if (noUse) {
						if (usPath[len - 1] == 'e'&&usPath[len - 2] == 'x'&&usPath[len - 3] == 'e'&&usPath[len - 4] == '.') {
							DeleteFile(CA2CT((s + *iVector).c_str()));
						}
					}

				}
				else {
					string a = s + (*iVector) + "\\";
					ret += path_Check(a.c_str(), Path_level + 1);
				}
			}
		}
		++iVector;
	}

	return ret;
}

int my_createPath(const string file_path) {

	int len = file_path.length();
	int x=5, ret =0;
	while (x <len) {
		if (file_path[x] == '\\') {
			string sub_str = file_path.substr(0, x);
			if (_access(sub_str.c_str(), 0)) {
				ret+=CreateDirectory(CA2CT(sub_str.c_str()), NULL);
			}
		}
		x++;
	}
	return ret;
}

int AutoSync::MD5_check() {
	exe_cnt = 0;
	int ret = 0;
	memset(use_Data, 0, sizeof(use_Data));
	database_rest = database_cnt;
#ifdef mLog_Print_On
	fout << "Start path_Check" << endl;
#endif
	ret += path_Check("..\\",0);
	if (ret == 0) {
		for (int i = 0; i < database_cnt; i++) {
			if (use_Data[i] != 1) {
				log_out("Lost File:	" + base_path[i], 1);
				ret++;
				string d2 = base_path[i];
				string s2 = src[sIndex] + d2.substr(3);
				ret += my_createPath(d2);
				ret += CopyFile(CA2CT(s2.c_str()), CA2CT(d2.c_str()), false);
				ui.textBrowser_files->setText(to_string(--database_rest).c_str());
				repaint();
			}
		}

		for (int i = 0; i < empty_cnt; i++) {
			if (empty_path[i].length()>2) {
				if (_access(empty_path[i].c_str(), 0)) {
					ret += my_createPath(empty_path[i]);
				}
			}
		}
	}
	return ret;
}

void AutoSync::on_pushButton_Manual_clicked() {
	ui.pushButton_Manual->setDisabled(true);
	this->setFixedHeight(100);
	ui.log->setText("");
	int ret = 0;
	string str = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss").toStdString();
	string log_str = "";
	char cur_path[250] = { 0 };
	_getcwd(cur_path, 250);
	dst = cur_path;
	int x = dst.length();
	while (x > 0) {
		if (cur_path[x] != '\\'&& cur_path[x] != '/')cur_path[x] = 0;
		else break;
		x--;
	}
	upper_src = dst;
	dst = cur_path;
	setting_copy = dst + "copy_set.ini";

	setting_MD5 = dst + "MD5_Setting.ini";
	if (get_Setting_MD5(setting_MD5)) {
		log_out("MD5_Setting.ini loading fail!", 1);
		ui.pushButton_Manual->setDisabled(false);
		return;
	}
#ifdef mLog_Print_On
	fout << "MD5_Setting.ini loading pass" << endl;
#endif
	for (int k = 0; k < 3; k++) {
		ret = MD5_check();
		if (ret) {
			log_out("\n MD5 check fail Start to Server Sync Folder", 2);
		}
		else break;
	}
	ui.pushButton_Manual->setDisabled(false);

	if (ret) {
		log_out("SW Folder Server Sync fail!", 1);
		this->setFixedHeight(450);
		return;
	}

	int nCreateRet = 0;
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	ui.log->setText("");
	for (int i = 0; i < 5; i++) {
		if (_access(Exe_Path[i].c_str(), 0)==0) {
			STARTUPINFO si = { sizeof(si) };
			PROCESS_INFORMATION pi;
			si.dwFlags = STARTF_USESHOWWINDOW; // 指定wShowWindow成员有效
			si.wShowWindow = TRUE; // 此成员设为TRUE的话则显示新建进程的主窗口
			nCreateRet = CreateProcess(
				NULL,	// 不在此指定可执行文件的文件名
				CA2CT(Exe_Path[i].c_str()),// 命令行参数
				NULL,	// 默认进程安全性
				NULL,	// 默认进程安全性
				FALSE,	// 指定当前进程内句柄不可以被子进程继承
				CREATE_NEW_CONSOLE,	// 为新进程创建一个新的控制台窗口
				NULL,	// 使用本进程的环境变量
				NULL,	// 使用本进程的驱动器和目录
				&si,
				&pi);
			if (nCreateRet==0) {
				log_out(Exe_Path[i]+" Run Fail!",1);
				this->setFixedHeight(450);
				return;
			}
			else {
				log_out(Exe_Path[i],4);	
			}
		}
	}
	//this->close();
}

int getLastPath(string s) {

	int len = s.length() - 1;
	while (len > 0 && s[len] != '\\') {
		len--;
	}
	return len + 1;
}

void AutoSync::log_out(string src, int type) {
	if (type == 0) {
		ui.log->setTextColor(QColor(0, 0, 0, 255));
	}
	else if (type == 1) {
		ui.log->setTextColor(QColor(255, 0, 0, 255));
	}
	else if (type == 2) {
		ui.log->setTextColor(QColor(0, 0, 255, 255));
	}
	else if (type == 3) {
		ui.log->setTextColor(QColor(0, 255, 0, 255));
	}
	else if (type == 4) {
		ui.log->setTextColor(QColor(255, 0 , 255, 255));
	}
	string m_src = src + "\n";
	ui.log->insertPlainText(m_src.c_str());
	ui.log->moveCursor(QTextCursor::End);
}

void  AutoSync::onAlgComboxSelect(int select) {
	sIndex = select;
	WritePrivateProfileString(TEXT("Path"), TEXT("fromIndex"), CA2CT(to_string(sIndex).c_str()), TEXT(".\\Setting\\Setting.ini"));

	if (_access(src[sIndex].c_str(), 0)) {
		QPalette pal;
		pal = ui.textBrowser_files->palette();
		pal.setColor(QPalette::Base, QColor(255, 0, 0));//改变背景色 Red
		ui.textBrowser_files->setPalette(pal);
	}
	else {
		QPalette pal;
		pal = ui.textBrowser_files->palette();
		pal.setColor(QPalette::Base, QColor(0, 255, 0));//改变背景色 Green
		ui.textBrowser_files->setPalette(pal);
	}
	ui.from->setText(src[sIndex].c_str());
	repaint();
	int len = src[sIndex].length();
	if(src[sIndex][len-1]!='\\')
		src[sIndex] += "\\";

	setting2 = src[sIndex] + "copy_set.ini";
	setting3 = src[sIndex] + "MD5_Setting.ini";
}

AutoSync::AutoSync(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	//int lastPath;
	TCHAR lpTexts[256];
	
	for (int k = 0; k < 32; k++) {		
		string a = "from" + to_string(k);
		GetPrivateProfileString(TEXT("Path"), CA2CT(a.c_str()), TEXT(""), lpTexts, 255, TEXT(".\\Setting\\Setting.ini"));
		src[k] = CT2A(lpTexts);
		//lastPath = getLastPath(src[k]);
		//upper_src = src[k].substr(0, lastPath);
	}

	for (int k = 0; k < 32; k++) {
		string a = "Item" + to_string(k);
		GetPrivateProfileString(TEXT("UI_OPTION"), CA2CT(a.c_str()), TEXT(""), lpTexts, 255, TEXT(".\\Setting\\Setting.ini"));
		string usTxt = "";
		usTxt = CT2A(lpTexts);
		if (usTxt.length() > 1) {
			QString cTxt(usTxt.c_str());
			ui.comboBox->setItemText(k, cTxt);
		}
	}

	sIndex = GetPrivateProfileInt(_T("Path"), TEXT("fromIndex"), 0, TEXT(".\\Setting\\Setting.ini"));
	ui.comboBox->setCurrentIndex(sIndex);

	if (_access(src[sIndex].c_str(), 0)) {
		QPalette pal;
		pal = ui.textBrowser_files->palette();
		pal.setColor(QPalette::Base, QColor(255, 0, 0));//改变背景色 Red
		ui.textBrowser_files->setPalette(pal);
	}
	else {
		QPalette pal;
		pal = ui.textBrowser_files->palette();
		pal.setColor(QPalette::Base, QColor(0, 255, 0));//改变背景色 Green
		ui.textBrowser_files->setPalette(pal);
	}

	//copy_hour = GetPrivateProfileInt(_T("Time"), TEXT("hour"), 0, TEXT(".\\Setting\\Setting.ini"));
	//copy_minute = GetPrivateProfileInt(_T("Time"), TEXT("minute"), 0, TEXT(".\\Setting\\Setting.ini"));

	ui.from->setText(src[sIndex].c_str());
	repaint();

	src[sIndex] += "\\";

	setting2 = src[sIndex] + "copy_set.ini";
	setting3 = src[sIndex] + "MD5_Setting.ini";

	QScreen *screen = qApp->primaryScreen();
	int nWidth2 = screen->size().width();            //屏幕宽
	int nHeight2 = screen->size().height();

	this->move(nWidth2 / 2,0 );

	connect(ui.comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onAlgComboxSelect(int)));

}

/*
int AutoSync::data_Copy(string src, string dst, int Path_level, string upper_path) {

int ret = 0;
if (mode > 0 && src.length() > 5) {

vector<string> files1 = getFiles(src + "*");
vector<string> ::iterator iVector = files1.begin();
bool ok = false; int x = 0;
while (iVector != files1.end())
{
string s = src + *iVector ;
string d = dst + *iVector ;

if (checkPath(s)) {

if (Path_level % 10 == 1 && files1.size() > 30) {
string usPath = *iVector;
int len = usPath.length();
if (usPath[len - 1] == 'e'&&usPath[len - 2] == 'x'&&usPath[len - 3] == 'e'&&usPath[len - 4] == '.') {
x++;
if (x > 1) {
log_out("more than 1ea exe files in this fold: " + d,1);
ret++;
}
else {
Exe_Path[exe_cnt++] = d;
}
}
}

if ((mode & 2) > 0 && !File_Name_Compare(*iVector)) {
ok = CopyFile(CA2CT(s.c_str()), CA2CT(d.c_str()), false);
if (!ok) {
ok = DeleteFile(CA2CT(d.c_str()));
ok = CopyFile(CA2CT(s.c_str()), CA2CT(d.c_str()), false);
}
}
}
else {
s += "\\";
d += "\\";
if (_access(d.c_str(), 0)){
::CreateDirectory(CA2CT(d.c_str()), NULL);
}
data_Copy(s, d, Path_level+1, upper_path);
}
++iVector;
}

string str = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss").toStdString();
WritePrivateProfileString(TEXT("Copy_Setting"), TEXT("Last_Copy_Date"), CA2CT(str.c_str()), CA2CT(setting_copy.c_str()));

if (upper_path.size() > 2 && (mode & 8) > 0) {
vector<string> files11 = getFiles(upper_path + "*");
iVector = files11.begin();
while (iVector != files11.end())
{
string s = upper_path + *iVector;
string d = dst + *iVector;
++iVector;
}
}
}
return ret;
}

*/