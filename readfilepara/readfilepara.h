// readfilepara.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CreadfileparaApp:
// �йش����ʵ�֣������ readfilepara.cpp
//

class CreadfileparaApp : public CWinApp
{
public:
	CreadfileparaApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CreadfileparaApp theApp;