
// mixerDlg.cpp : ÊµÏÖÎÄ¼þ
//

#include "stdafx.h"
#include "mixer.h"
#include "mixerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CmixerDlg




CmixerDlg::CmixerDlg(CWnd *pParent /*=NULL*/)
    : CDialogEx(CmixerDlg::IDD, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmixerDlg::DoDataExchange(CDataExchange *pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_SLIDER_WAVE, slider_WAVE);
    DDX_Control(pDX, IDC_SLIDER_SW, slider_SW);
    DDX_Control(pDX, IDC_SLIDER_CD, slider_CD);
    DDX_Control(pDX, IDC_SLIDER_LINE, slider_LINE);
    DDX_Control(pDX, IDC_SLIDER_MIC, slider_MIC);
    DDX_Control(pDX, IDC_CHECK1, check_WAVE);
    DDX_Control(pDX, IDC_CHECK2, check_SW);
    DDX_Control(pDX, IDC_CHECK3, check_CD);
    DDX_Control(pDX, IDC_CHECK4, check_LINE);
    DDX_Control(pDX, IDC_CHECK5, check_MIC);
}

BEGIN_MESSAGE_MAP(CmixerDlg, CDialogEx)
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_WAVE, &CmixerDlg::OnNMCustomdrawSliderWave)
    ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_SW, &CmixerDlg::OnNMCustomdrawSliderSw)
    ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_CD, &CmixerDlg::OnNMCustomdrawSliderCd)
    ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_LINE, &CmixerDlg::OnNMCustomdrawSliderLine)
    ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_MIC, &CmixerDlg::OnNMCustomdrawSliderMic)
    ON_BN_CLICKED(IDC_CHECK1, &CmixerDlg::OnBnClickedCheck1)
    ON_BN_CLICKED(IDC_CHECK2, &CmixerDlg::OnBnClickedCheck2)
    ON_BN_CLICKED(IDC_CHECK3, &CmixerDlg::OnBnClickedCheck3)
    ON_BN_CLICKED(IDC_CHECK4, &CmixerDlg::OnBnClickedCheck4)
    ON_BN_CLICKED(IDC_CHECK5, &CmixerDlg::OnBnClickedCheck5)
    ON_MESSAGE(MM_MIXM_LINE_CHANGE, &CmixerDlg::OnMLChange)
    ON_MESSAGE(MM_MIXM_CONTROL_CHANGE, &CmixerDlg::OnMCChange)
END_MESSAGE_MAP()
void fool()
{

}
void CmixerDlg::InitMixer()
{
    // /////enum mix device
    // MIXERCAPS mixcaps;
    // unsigned long iNumDevs, i;
    // iNumDevs = mixerGetNumDevs(); //get the num of mixer
    // for (i = 0; i < iNumDevs; i++)
    // {
    //     if (!mixerGetDevCaps(i, &mixcaps, sizeof(MIXERCAPS)))
    //     {
    //         printf("Device ID #%u: %s\r\n", i, mixcaps.szPname);
    //     }
    // }
    // //////open default mix out deive£»


    err = mixerOpen(&mixerHandle, 0, (DWORD)this->m_hWnd, NULL, MIXER_OBJECTF_MIXER | CALLBACK_WINDOW);
    //get detination lineinfo
    mixerline.cbStruct = sizeof(MIXERLINE);
    mixerline.dwDestination = 0;  //
    mixerGetLineInfo((HMIXEROBJ)mixerHandle, &mixerline, MIXER_GETLINEINFOF_DESTINATION);
    //get source lineinfo
    for (int i = 0; i < mixerline.cConnections; ++i)
    {
        mixerlinesource.cbStruct = sizeof(MIXERLINE);
        mixerlinesource.dwDestination = 0;
        mixerlinesource.dwSource = i ;
        mixerGetLineInfo((HMIXEROBJ)mixerHandle, &mixerlinesource, MIXER_GETLINEINFOF_SOURCE);
    }

    GET_MIXER_LINECTR(WAVE, 0);
    GET_MIXER_LINECTR(SW, 0X10000);
    GET_MIXER_LINECTR(CD, 0X20000);
    GET_MIXER_LINECTR(LINE, 0XA0000);
    GET_MIXER_LINECTR(MIC, 0XC0000);

    GET_CONTROL_DETAIL_VOLUME(WAVE);
    GET_CONTROL_DETAIL_VOLUME(SW);
    GET_CONTROL_DETAIL_VOLUME(CD);
    GET_CONTROL_DETAIL_VOLUME(LINE);
    GET_CONTROL_DETAIL_VOLUME(MIC);

    GET_CONTROL_DETAIL_MUTE(WAVE);
    GET_CONTROL_DETAIL_MUTE(SW);
    GET_CONTROL_DETAIL_MUTE(CD);
    GET_CONTROL_DETAIL_MUTE(LINE);
    GET_CONTROL_DETAIL_MUTE(MIC);

    CHECK_SET(WAVE);
    CHECK_SET(CD);
    CHECK_SET(SW);
    CHECK_SET(LINE);
    CHECK_SET(MIC);

    SLIDER_SET(WAVE);
    SLIDER_SET(CD);
    SLIDER_SET(SW);
    SLIDER_SET(LINE);
    SLIDER_SET(MIC);

}
// CmixerDlg

BOOL CmixerDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    SetIcon(m_hIcon, TRUE);
    SetIcon(m_hIcon, FALSE);
    ShowWindow(SW_MINIMIZE);

    SLIDER_INIT(WAVE);
    SLIDER_INIT(CD);
    SLIDER_INIT(SW);
    SLIDER_INIT(LINE);
    SLIDER_INIT(MIC);

    InitMixer();

    return TRUE;
}

void CmixerDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); //

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);


        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;


        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialogEx::OnPaint();
    }
}


HCURSOR CmixerDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}



void CmixerDlg::OnNMCustomdrawSliderWave(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

    *pResult = 0;
    SET_CTRLDEL_VOLUME_SLIDER(WAVE);
}


void CmixerDlg::OnNMCustomdrawSliderSw(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

    *pResult = 0;
    SET_CTRLDEL_VOLUME_SLIDER(SW);
}


void CmixerDlg::OnNMCustomdrawSliderCd(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
    *pResult = 0;
    SET_CTRLDEL_VOLUME_SLIDER(CD);
}


void CmixerDlg::OnNMCustomdrawSliderLine(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
    *pResult = 0;
    SET_CTRLDEL_VOLUME_SLIDER(LINE);
}


void CmixerDlg::OnNMCustomdrawSliderMic(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
    *pResult = 0;
    SET_CTRLDEL_VOLUME_SLIDER(MIC);
}


void CmixerDlg::OnBnClickedCheck1()
{
    SET_CTRLDEL_MUTE_CHECK(WAVE);
}


void CmixerDlg::OnBnClickedCheck2()
{
    SET_CTRLDEL_MUTE_CHECK(SW);
}


void CmixerDlg::OnBnClickedCheck3()
{
    SET_CTRLDEL_MUTE_CHECK(CD);

}


void CmixerDlg::OnBnClickedCheck4()
{
    SET_CTRLDEL_MUTE_CHECK(LINE);

}


void CmixerDlg::OnBnClickedCheck5()
{
    SET_CTRLDEL_MUTE_CHECK(MIC);

}
LONG   CmixerDlg::OnMCChange(WPARAM wParam, LPARAM lParam)
{
#define GET_CONTROL_CHANGE_VOL(STH) if(lParam == mixerControlArray_##STH[0].dwControlID){ \
        GET_CONTROL_DETAIL_VOLUME(STH);SLIDER_SET(STH);\
    }
#define GET_CONTROL_CHANGE_MUTE(STH) if(lParam == mixerControlArray_##STH[1].dwControlID){\
        GET_CONTROL_DETAIL_MUTE(STH);CHECK_SET(STH);\
    }

    GET_CONTROL_CHANGE_VOL(WAVE);
    GET_CONTROL_CHANGE_VOL(SW);
    GET_CONTROL_CHANGE_VOL(CD);
    GET_CONTROL_CHANGE_VOL(LINE);
    GET_CONTROL_CHANGE_VOL(MIC);
    GET_CONTROL_CHANGE_MUTE(WAVE);
    GET_CONTROL_CHANGE_MUTE(SW);
    GET_CONTROL_CHANGE_MUTE(CD);
    GET_CONTROL_CHANGE_MUTE(LINE);
    GET_CONTROL_CHANGE_MUTE(MIC);
    return 0;
}
LONG   CmixerDlg::OnMLChange(WPARAM wParam, LPARAM lParam)
{
    return 0;
}