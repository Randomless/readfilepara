// readfileparaDlg.cpp : ʵ���ļ�
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

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CreadfileparaDlg �Ի���




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


// CreadfileparaDlg ��Ϣ�������

BOOL CreadfileparaDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CreadfileparaDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CreadfileparaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//�ַ��ָ��
vector<string> split(const string& str, const string& delim)
{
	vector<string> res;
	if("" == str) return res;
	//�Ƚ�Ҫ�и���ַ�����string����ת��Ϊchar*����
	char * strs = new char[str.length() + 1] ; //��Ҫ����
	strcpy(strs, str.c_str()); //string��������copy��char����

	char * d = new char[delim.length() + 1];
	strcpy(d, delim.c_str());

	char *p = strtok(strs, d);
	while(p) {
		string s = p; //�ָ�õ����ַ���ת��Ϊstring����
		res.push_back(s); //����������
		p = strtok(NULL, d);
	}

	return res;
}

//ת����string����
template<class T>
string toString(const T& t)
{
	stringstream oss;//����һ����
 	oss.precision(8); //������Ч���ָ���
	oss<<t;//��ֵ����������
	return oss.str();//��ȡת������ַ�ת������д��result
    oss.clear();
}
//����ת������convert
template<class out_type,class in_value>
out_type convert(const in_value & t)
{
	stringstream stream;
	stream<<t;//�����д�ֵ
	out_type result;//����洢ת�����
	stream>>result;//��result��д��ֵ
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������

    AfxMessageBox(L"ѡ��Ҫ���浽���ݿ��data.txt�ļ���");
	CString strtmp;
	string s;//������һ������
	ifstream f1;  
	CString Filter=L"�ļ�(*.txt)|*.txt||";
	bool isopen=true;
	CFileDialog cf(isopen,L"txt", NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, Filter, NULL);
	// CFileDialog���װ��Windows���õ��ļ��Ի��򡣳��õ��ļ��Ի����ṩ��һ�ּ򵥵���Windows��׼��һ�µ��ļ��򿪺��ļ����̶Ի����ܡ�
	//BOOL bOpenFileDialog,  
	//TRUE����ʾ���ļ��Ի���FALSE����ʾ�����ļ��Ի���
	if(cf.DoModal()==IDOK)   //DoModal��ʾ�Ի���ʹ�û����Խ���ѡ��,DoModal()�ķ���ֵΪIDOK��IDCANCEL�������������ڶԻ�����ѡ��ȷ�ϡ����ǡ�ȡ����
	{
		strtmp=cf.GetPathName(); //GetPathName����ѡ���ļ�������·��
	}
	else
	{
		AfxMessageBox(L"û��ѡ���ļ���");exit(0);// exit(1)��ʾ�쳣�˳�.exit(0)��ʾ�����˳�   
	}
	f1.open(strtmp,ios::in);
	if(f1.fail())
	{
		cout<<"�ļ���ʧ��"<<endl;
		exit(1);
	}

	while(!f1.eof())
	{   
		getline(f1,s); // f1.getline(char*,n);
		if(s!="") //��ֹ���һ��Ϊ��
		{
			vector<string> str=split(s,",");
			if(0<str.size()<=10)
			{
				str.push_back("0"); //����ֵ����д���һλΪ0
			}
			para data;
		//	textdata.push_back(data);
            vector<para> data_vec;
			//    ={str[1],str[2],atoi(str[2].c_str())};

			data.m_strStation=str[0];  //atoi atof �ַ������͵�ת����int��double����double��16λ�ģ�Ҫ���漸λ�ο�������룬���ʱ��iomanip�еĺ������ƣ�
			data.m_strPname=str[1];
			data.m_iStime=atoi(str[2].c_str());
			data.m_strRL=str[3];
			data.m_dHangle=atof(str[4].c_str());         //float b = floor(data.m_dHangle * 100000.000f + 0.5) / 100000.000f; С����λ��ת��Ϊ5λ
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

	AfxMessageBox(L"ѡ�������ļ�����·����");
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

// 	  // forѭ������textdata
//      for (size_t j=0;j<=textdata.size()-1;j++)
//     {
//        if (j >= textdata.size() || j < 0) { cout << "vetcor�±�Խ��" << endl; break; }
//       f2<<textdata[j].m_strStation<<textdata[j].m_strPname<<"\n";
//     }

      // iterator����textdata
     for (vector<para>::iterator i = textdata.begin(); i != textdata.end(); ++i) 
	 {
		f2<<(*i).m_strStation<<(*i).m_strPname<<(*i).m_iStime<<(*i).m_strRL<<(*i).m_dHangle
		  <<(*i).m_dVangle<<(*i).m_dSdistance<<(*i).m_dHdistance<<(*i).m_dHinstru<<(*i).m_dHpr<<(*i).m_dTc
          <<"\n";
	 }
	 AfxMessageBox(L"�ѱ����ȡ��Ϣ...");

//����Ϊsqlite����.db
   sqlite3 *db;
   char *err_msg;
   int rc;
   char *sql;

   //�����ݿ�,��������;
   rc = sqlite3_open("D:\\test.db", &db);
	if( rc ){
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		exit(0);
	}else{
		fprintf(stdout, "Opened database successfully\n");
	}

   //дSQL������һ�ű�;
   sql="CREATE TABLE test01("\
	   "StationName text  NULL,PointName text,SurveyTime integer,"\
	   "RL text,Hangle real,Vangle real,Sdistance real,Hdistance real,HighInstru real,HighPrism real,TwoC real);";  
   //�������в���Ϊ�գ���ô����ΪNOT NULL, �������п���Ϊ�գ���ô����Ϊ NULL�����߲�����

   //ִ��sql������db�ļ�
    rc = sqlite3_exec(db, sql, callback, 0, &err_msg);
	if( rc != SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n",err_msg);
		sqlite3_free(err_msg);
	}else{
		fprintf(stdout, "Table created successfully\n");
	}

    //дSQL���ڱ��в�������;
   for(vector<para>::iterator i = textdata.begin(); i != textdata.end(); ++i)
   {    
	   sql="";  //��ʼ��sql
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

 
      sql=const_cast<char *>(link.c_str()); //����һ��ָ��ǳ�����ָ��
      rc = sqlite3_exec(db, sql, callback, 0, &err_msg);

   }

	sqlite3_close(db);

    f2.close();
}

void CreadfileparaDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	   //delete������
	sqlite3 *del;
	char *err_msg;
	int rd;
	 char* delsql;
    
// 	AfxMessageBox(L"ѡ��Ҫɾ�������ݿ�·����");
// 	CString delpath,delname;
// 	// char path[100];
// 	ofstream fdel;
// 	CString Filter=L"�ļ�(*.db)|*.db||";
// 	CFileDialog delfile(FALSE,L"db", NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, Filter, NULL);
// 	if (delfile.DoModal()==IDOK)
// 	{
// 		delpath=delfile.GetPathName();
// 		delname=delfile.GetFileName(); //������չ��
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
		   fprintf(stderr, "�޷������ݿ�: %s", sqlite3_errmsg(del));
	 
	   }
       delsql="DELETE from test01;";
	    rd = sqlite3_exec(del, delsql, callback, 0, &err_msg);
		sqlite3_close(del);
		AfxMessageBox(L"�����d:\\test.db�е�test01");

}
