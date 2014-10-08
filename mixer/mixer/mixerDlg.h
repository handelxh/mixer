
// mixerDlg.h : 头文件
//

#pragma once
#include "Mmsystem.h "

// CmixerDlg 对话框
class CmixerDlg : public CDHtmlDialog
{
// 构造
public:
	CmixerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MIXER_DIALOG, IDH = IDR_HTML_MIXER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	HRESULT OnButtonOK(IHTMLElement *pElement);
	HRESULT OnButtonCancel(IHTMLElement *pElement);

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()
};
