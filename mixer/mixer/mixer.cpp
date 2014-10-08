
// mixer.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "mixer.h"
#include "mixerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CmixerApp

BEGIN_MESSAGE_MAP(CmixerApp, CWinApp)
    ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CmixerApp ����

CmixerApp::CmixerApp()
{
    // ֧����������������
    m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

    // TODO: �ڴ˴���ӹ�����룬
    // ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CmixerApp ����

CmixerApp theApp;

// MMRESULT mixerGetDevCaps(
// UINT_PTR uMxId,
// LPMIXERCAPS pmxcaps,
// UINT cbmxcaps
// );

void initMixer(void)
{
    // UINT mixerno = mixerGetNumDevs();
    // UINT_PTR uMxId =0 ;
    // LPMIXERCAPS pmxcaps;
    // UINT cbmxcaps = sizeof(MIXERCAPS);
    // MMRESULT mr;
    // mr = mixerGetDevCaps(uMxId,pmxcaps,cbmxcaps);
    MIXERCAPS     mixcaps;
    unsigned long iNumDevs, i;
    iNumDevs = mixerGetNumDevs();
    for (i = 0; i < iNumDevs; i++)
    {

        if (!mixerGetDevCaps(i, &mixcaps, sizeof(MIXERCAPS)))
        {

            //printf("Device ID #%u: %s\r\n", i, mixcaps.szPname);
        }
    }
    unsigned long err;
    HMIXER        mixerHandle;
    WAVEFORMATEX  waveFormat;
    HWAVEOUT      hWaveOut;
}


// CmixerApp ��ʼ��
BOOL CmixerApp::InitInstance()
{
    // ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
    // ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
    //����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
    INITCOMMONCONTROLSEX InitCtrls;
    InitCtrls.dwSize = sizeof(InitCtrls);
    // ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
    // �����ؼ��ࡣ
    // initMixer();
    InitCtrls.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&InitCtrls);

    CWinApp::InitInstance();


    AfxEnableControlContainer();

    // ���� shell ���������Է��Ի������
    // �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
    CShellManager *pShellManager = new CShellManager;

    // ��׼��ʼ��
    // ���δʹ����Щ���ܲ�ϣ����С
    // ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
    // ����Ҫ���ض���ʼ������
    // �������ڴ洢���õ�ע�����
    // TODO: Ӧ�ʵ��޸ĸ��ַ�����
    // �����޸�Ϊ��˾����֯��
    SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

    CmixerDlg dlg;
    m_pMainWnd = &dlg;
    INT_PTR nResponse = dlg.DoModal();
    if (nResponse == IDOK)
    {
        // TODO: �ڴ˷��ô����ʱ��
        //  ��ȷ�������رնԻ���Ĵ���
    }
    else if (nResponse == IDCANCEL)
    {
        // TODO: �ڴ˷��ô����ʱ��
        //  ��ȡ�������رնԻ���Ĵ���
    }

    // ɾ�����洴���� shell ��������
    if (pShellManager != NULL)
    {
        delete pShellManager;
    }

    // ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
    //  ����������Ӧ�ó������Ϣ�á�
    return FALSE;
}

