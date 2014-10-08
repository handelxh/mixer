
// mixerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "mixer.h"
#include "mixerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CmixerDlg 对话框

BEGIN_DHTML_EVENT_MAP(CmixerDlg)
DHTML_EVENT_ONCLICK(_T("ButtonOK"), OnButtonOK)
DHTML_EVENT_ONCLICK(_T("ButtonCancel"), OnButtonCancel)
END_DHTML_EVENT_MAP()



CmixerDlg::CmixerDlg(CWnd *pParent /*=NULL*/)
    : CDHtmlDialog(CmixerDlg::IDD, CmixerDlg::IDH, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmixerDlg::DoDataExchange(CDataExchange *pDX)
{
    CDHtmlDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CmixerDlg, CDHtmlDialog)
END_MESSAGE_MAP()
//init mixer out
void InitMixer()
{
    // /////enum mix device
    // MIXERCAPS mixcaps;
    // unsigned long iNumDevs, i;
    // iNumDevs = mixerGetNumDevs();
    // for (i = 0; i < iNumDevs; i++)
    // {
    //     if (!mixerGetDevCaps(i, &mixcaps, sizeof(MIXERCAPS)))
    //     {
    //         printf("Device ID #%u: %s\r\n", i, mixcaps.szPname);
    //     }
    // }
    // //////open default mix out deive；
    unsigned long err;
    HMIXER        mixerHandle;
    err = mixerOpen(&mixerHandle, 0, 0, 0, 0);
    //get detination lineinfo
    MIXERLINE     mixerline,mixerlinesource;
    mixerline.cbStruct = sizeof(MIXERLINE);
    mixerline.dwDestination = 0;
    mixerGetLineInfo((HMIXEROBJ)mixerHandle, &mixerline, MIXER_GETLINEINFOF_DESTINATION);
    //get source lineinfo
    for (int i = 0; i < mixerline.cConnections; ++i)
    {
    	mixerlinesource.cbStruct = sizeof(MIXERLINE);
    	mixerlinesource.dwDestination = 0;
		mixerlinesource.dwSource = i ;
        mixerGetLineInfo((HMIXEROBJ)mixerHandle, &mixerlinesource, MIXER_GETLINEINFOF_SOURCE);
    }
    //mixer line control
    MIXERLINECONTROLS  mixerlinecontrol;




}

// CmixerDlg 消息处理程序

BOOL CmixerDlg::OnInitDialog()
{
    CDHtmlDialog::OnInitDialog();

    // 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
    //  执行此操作
    SetIcon(m_hIcon, TRUE);         // 设置大图标
    SetIcon(m_hIcon, FALSE);        // 设置小图标

    ShowWindow(SW_MINIMIZE);
    InitMixer();

    // TODO: 在此添加额外的初始化代码

    return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CmixerDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // 用于绘制的设备上下文

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // 使图标在工作区矩形中居中
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
        CDHtmlDialog::OnPaint();
    }
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CmixerDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

HRESULT CmixerDlg::OnButtonOK(IHTMLElement * /*pElement*/)
{
    OnOK();
    return S_OK;
}

HRESULT CmixerDlg::OnButtonCancel(IHTMLElement * /*pElement*/)
{
    OnCancel();
    return S_OK;
}
