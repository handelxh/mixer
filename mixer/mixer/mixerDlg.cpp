
// mixerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mixer.h"
#include "mixerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CmixerDlg �Ի���

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
    // //////open default mix out deive��
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

// CmixerDlg ��Ϣ�������

BOOL CmixerDlg::OnInitDialog()
{
    CDHtmlDialog::OnInitDialog();

    // ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
    //  ִ�д˲���
    SetIcon(m_hIcon, TRUE);         // ���ô�ͼ��
    SetIcon(m_hIcon, FALSE);        // ����Сͼ��

    ShowWindow(SW_MINIMIZE);
    InitMixer();

    // TODO: �ڴ���Ӷ���ĳ�ʼ������

    return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CmixerDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // ���ڻ��Ƶ��豸������

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // ʹͼ���ڹ����������о���
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
        CDHtmlDialog::OnPaint();
    }
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
