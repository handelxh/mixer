
// mixer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "Mmsystem.h "
#pragma comment(lib,"Winmm.lib")

// CmixerApp:
// �йش����ʵ�֣������ mixer.cpp
//

class CmixerApp : public CWinApp
{
public:
	CmixerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CmixerApp theApp;