// readfileparaDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "readfilepara.h"
#include "readfileparaDlg.h"
#include "sqlite3.h"
#include "CppSQLite3.h"
#include <iostream> 
#include <fstream> 
#include <vector> 
#include <string> 
#include <sstream>
#include <math.h>
#include <algorithm>
#include <iterator>
#include <iomanip>

// #pragma comment(linker, "./lib/sqlite3.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CreadfileparaDlg 对话框




CreadfileparaDlg::CreadfileparaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CreadfileparaDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CreadfileparaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CreadfileparaDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON2, &CreadfileparaDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CreadfileparaDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CreadfileparaDlg 消息处理程序

BOOL CreadfileparaDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CreadfileparaDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CreadfileparaDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CreadfileparaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//字符分割函数
vector<string> split(const string& str, const string& delim)
{
	vector<string> res;
	if("" == str) return res;
	//先将要切割的字符串从string类型转换为char*类型
	char * strs = new char[str.length() + 1] ; //不要忘了
	strcpy(strs, str.c_str()); //string类型内容copy给char类型

	char * d = new char[delim.length() + 1];
	strcpy(d, delim.c_str());

	char *p = strtok(strs, d);
	while(p) {
		string s = p; //分割得到的字符串转换为string类型
		res.push_back(s); //存入结果数组
		p = strtok(NULL, d);
	}

	return res;
}

//转换成string函数
template<class T>
string toString(const T& t)
{
	stringstream oss;//创建一个流
 	oss.precision(8); //保存有效数字个数
	oss<<t;//把值传递如流中
	return oss.str();//获取转换后的字符转并将其写入result
    oss.clear();
}
//类型转换函数convert
template<class out_type,class in_value>
out_type convert(const in_value & t)
{
	stringstream stream;
	stream<<t;//向流中传值
	out_type result;//这里存储转换结果
	stream>>result;//向result中写入值
	return result;
}


struct para
{
	string m_strStation;
	string m_strPname;
	int m_iStime;
	string m_strRL;
	double m_dHangle;
	double m_dVangle;
	double m_dSdistance;
	double m_dHdistance;
	double m_dHinstru;
	double m_dHpr;
	double m_dTc;

};
int i=0;
vector<para> textdata;

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
	int i;
	for(i=0; i<argc; i++){
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

void CreadfileparaDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

    AfxMessageBox(L"选择要保存到数据库的data.txt文件！");
	CString strtmp;
	string s;//存读入的一行数据
	ifstream f1;  
	CString Filter=L"文件(*.txt)|*.txt||";
	bool isopen=true;
	CFileDialog cf(isopen,L"txt", NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, Filter, NULL);
	// CFileDialog类封装了Windows常用的文件对话框。常用的文件对话框提供了一种简单的与Windows标准相一致的文件打开和文件存盘对话框功能。
	//BOOL bOpenFileDialog,  
	//TRUE则显示打开文件对话框，FALSE则显示保存文件对话框。
	if(cf.DoModal()==IDOK)   //DoModal显示对话框并使用户可以进行选择,DoModal()的返回值为IDOK，IDCANCEL。表明操作者在对话框上选择“确认”或是“取消”
	{
		strtmp=cf.GetPathName(); //GetPathName返回选定文件的完整路径
	}
	else
	{
		AfxMessageBox(L"没有选择文件！");exit(0);// exit(1)表示异常退出.exit(0)表示正常退出   
	}
	f1.open(strtmp,ios::in);
	if(f1.fail())
	{
		cout<<"文件打开失败"<<endl;
		exit(1);
	}

	while(!f1.eof())
	{   
		getline(f1,s); // f1.getline(char*,n);
		if(s!="") //防止最后一行为空
		{
			vector<string> str=split(s,",");
			if(0<str.size()<=10)
			{
				str.push_back("0"); //若空值，填写最后一位为0
			}
			para data;
		//	textdata.push_back(data);
            vector<para> data_vec;
			//    ={str[1],str[2],atoi(str[2].c_str())};

			data.m_strStation=str[0];  //atoi atof 字符串类型的转换成int和double。（double是16位的，要保存几位参考下面代码，输出时用iomanip中的函数控制）
			data.m_strPname=str[1];
			data.m_iStime=atoi(str[2].c_str());
			data.m_strRL=str[3];
			data.m_dHangle=atof(str[4].c_str());         //float b = floor(data.m_dHangle * 100000.000f + 0.5) / 100000.000f; 小数点位数转换为5位
			data.m_dVangle=atof(str[5].c_str());
			data.m_dSdistance=atof(str[6].c_str());
			data.m_dHdistance=atof(str[7].c_str());
			data.m_dHinstru=atof(str[8].c_str());
			data.m_dHpr=atof(str[9].c_str());
			data.m_dTc=atof(str[10].c_str());
			textdata.push_back(data);
			i++;
		}
	}  
    
	f1.close();	   

	AfxMessageBox(L"选择数据文件保存路径！");
	CString savepath;
	ofstream f2;  
	CFileDialog savefile(FALSE,L"txt", NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, Filter, NULL);
    if (savefile.DoModal()==IDOK)
    {
       savepath=savefile.GetPathName();
    }
	f2.open(savepath,ios_base::out);
	
	if (f2.fail())
	{
		AfxMessageBox(L"savefile fail...");exit(1);
	}

// 	  // for循环遍历textdata
//      for (size_t j=0;j<=textdata.size()-1;j++)
//     {
//        if (j >= textdata.size() || j < 0) { cout << "vetcor下标越界" << endl; break; }
//       f2<<textdata[j].m_strStation<<textdata[j].m_strPname<<"\n";
//     }

      // iterator遍历textdata
     for (vector<para>::iterator i = textdata.begin(); i != textdata.end(); ++i) 
	 {
		f2<<(*i).m_strStation<<(*i).m_strPname<<(*i).m_iStime<<(*i).m_strRL<<(*i).m_dHangle
		  <<(*i).m_dVangle<<(*i).m_dSdistance<<(*i).m_dHdistance<<(*i).m_dHinstru<<(*i).m_dHpr<<(*i).m_dTc
          <<"\n";
	 }
	 AfxMessageBox(L"已保存读取信息...");

//以下为sqlite创建.db
   sqlite3 *db;
   char *err_msg;
   int rc;
   char *sql;

   //打开数据库,创建连接;
   rc = sqlite3_open("D:\\test.db", &db);
	if( rc ){
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		exit(0);
	}else{
		fprintf(stdout, "Opened database successfully\n");
	}

   //写SQL，创建一张表;
   sql="CREATE TABLE test01("\
	   "StationName text  NULL,PointName text,SurveyTime integer,"\
	   "RL text,Hangle real,Vangle real,Sdistance real,Hdistance real,HighInstru real,HighPrism real,TwoC real);";  
   //如果这个列不能为空，那么设置为NOT NULL, 如果这个列可以为空，那么设置为 NULL，或者不设置

   //执行sql，创建db文件
    rc = sqlite3_exec(db, sql, callback, 0, &err_msg);
	if( rc != SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n",err_msg);
		sqlite3_free(err_msg);
	}else{
		fprintf(stdout, "Table created successfully\n");
	}

    //写SQL，在表中插入数据;
   for(vector<para>::iterator i = textdata.begin(); i != textdata.end(); ++i)
   {    
	   sql="";  //初始化sql
 	   string link="";
    //   link="insert into test01(StationName,PointName,SurveyTime,RL,Hangle,Vangle,Sdistance,Hdistance,HighInstru,HighPrism,TwoC)"\
            "VALUES ('GP02','GP01', 1, 'L',223.42555,89.38165,313.1830,313.1767,1.300,1.830,0); ";

	   link+="insert into test01 values(";
       link+="'"+convert<string>((*i).m_strStation)+"',";
	   link+="'"+convert<string>((*i).m_strPname)+"',";
	   link+=convert<string>((*i).m_iStime)+",";
	   link+="'"+convert<string>((*i).m_strRL)+"',";
	   link+=convert<string>((*i).m_dHangle)+",";
	   link+=convert<string>((*i).m_dVangle)+",";
	   link+=convert<string>((*i).m_dSdistance)+",";
	   link+=convert<string>((*i).m_dHdistance)+",";
       link+=convert<string>((*i).m_dHinstru)+",";
	   link+=convert<string>((*i).m_dHpr)+",";
	   link+=convert<string>((*i).m_dTc);
	   link+=");";

 
      sql=const_cast<char *>(link.c_str()); //返回一个指向非常量的指针
      rc = sqlite3_exec(db, sql, callback, 0, &err_msg);

   }

	sqlite3_close(db);

    f2.close();
}

void CreadfileparaDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	   //delete表数据
	sqlite3 *del;
	char *err_msg;
	int rd;
	 char* delsql;
    
// 	AfxMessageBox(L"选择要删除的数据库路径！");
// 	CString delpath,delname;
// 	// char path[100];
// 	ofstream fdel;
// 	CString Filter=L"文件(*.db)|*.db||";
// 	CFileDialog delfile(FALSE,L"db", NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, Filter, NULL);
// 	if (delfile.DoModal()==IDOK)
// 	{
// 		delpath=delfile.GetPathName();
// 		delname=delfile.GetFileName(); //包含拓展名
// 	}
// 	   char * delpath1=(char *)(LPCTSTR)delpath;
// 
// 	   rd = sqlite3_open(delpath1, &del);
// 	   if( rd){
// 		   fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(del));
// 		   exit(0);
// 	   }else{
// 		   fprintf(stdout, "Opened database successfully\n");
// 	   }
//      char * delname1=(char *)(LPCTSTR)delname;
// 	  char buf[20];
// 	  strcpy(buf,"DELETE from ");
// 	  strcat(buf,delname1);
// 	  string name(buf);
// 	   delsql =  name.c_str();
	   rd = sqlite3_open("D:\\test.db", &del);
	   if ( rd!= SQLITE_OK )
	   {
		   fprintf(stderr, "无法打开数据库: %s", sqlite3_errmsg(del));
	 
	   }
       delsql="DELETE from test01;";
	    rd = sqlite3_exec(del, delsql, callback, 0, &err_msg);
		sqlite3_close(del);
		AfxMessageBox(L"已清除d:\\test.db中的test01");

}
