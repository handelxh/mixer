
// mixerDlg.h : 头文件
//

#pragma once
#include "Mmsystem.h "
#include "afxcmn.h"
#include "afxwin.h"

// CmixerDlg 对话框
class CmixerDlg : public CDialogEx
{
    // 构造
public:
    CmixerDlg(CWnd *pParent = NULL);    // 标准构造函数

    // 对话框数据
    enum { IDD = IDD_MIXER_DIALOG };

protected:
    virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV 支持

public:
    // mixer func
    void InitMixer();  // init mixer and mixline and mixerlinesource
    //mixer
    HMIXER        mixerHandle;
    unsigned long err;
    MIXERLINE     mixerline, mixerlinesource;
    MIXERLINECONTROLS  mixerlinecontrol_WAVE;
    MIXERLINECONTROLS  mixerlinecontrol_SW;
    MIXERLINECONTROLS  mixerlinecontrol_CD;
    MIXERLINECONTROLS  mixerlinecontrol_LINE;
    MIXERLINECONTROLS  mixerlinecontrol_MIC;

    MIXERCONTROL       mixerControlArray_WAVE[2];
    MIXERCONTROL       mixerControlArray_SW[2];
    MIXERCONTROL       mixerControlArray_CD[2];
    MIXERCONTROL       mixerControlArray_LINE[2];
    MIXERCONTROL       mixerControlArray_MIC[2];

    MIXERCONTROLDETAILS_UNSIGNED    value_volume_WAVE;
    MIXERCONTROLDETAILS_UNSIGNED    value_volume_SW;
    MIXERCONTROLDETAILS_UNSIGNED    value_volume_CD;
    MIXERCONTROLDETAILS_UNSIGNED    value_volume_LINE;
    MIXERCONTROLDETAILS_UNSIGNED    value_volume_MIC;

    MIXERCONTROLDETAILS_BOOLEAN     value_mute_WAVE;
    MIXERCONTROLDETAILS_BOOLEAN     value_mute_CD;
    MIXERCONTROLDETAILS_BOOLEAN     value_mute_SW;
    MIXERCONTROLDETAILS_BOOLEAN     value_mute_LINE;
    MIXERCONTROLDETAILS_BOOLEAN     value_mute_MIC;

    MIXERCONTROLDETAILS    mixerControlDetails_VOLUME_WAVE;
    MIXERCONTROLDETAILS    mixerControlDetails_VOLUME_SW;
    MIXERCONTROLDETAILS    mixerControlDetails_VOLUME_CD;
    MIXERCONTROLDETAILS    mixerControlDetails_VOLUME_LINE;
    MIXERCONTROLDETAILS    mixerControlDetails_VOLUME_MIC;

    MIXERCONTROLDETAILS    mixerControlDetails_MUTE_SW;
    MIXERCONTROLDETAILS    mixerControlDetails_MUTE_CD;
    MIXERCONTROLDETAILS    mixerControlDetails_MUTE_LINE;
    MIXERCONTROLDETAILS    mixerControlDetails_MUTE_MIC;
    MIXERCONTROLDETAILS    mixerControlDetails_MUTE_WAVE;




    // 实现
protected:
    HICON m_hIcon;

    // 生成的消息映射函数
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()
public:
    CSliderCtrl slider_WAVE;
    CSliderCtrl slider_SW;
    CSliderCtrl slider_CD;
    CSliderCtrl slider_LINE;
    CSliderCtrl slider_MIC;
    CButton check_WAVE;
    CButton check_SW;
    CButton check_CD;
    CButton check_LINE;
    CButton check_MIC;
    afx_msg void OnNMCustomdrawSliderWave(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMCustomdrawSliderSw(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMCustomdrawSliderCd(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMCustomdrawSliderLine(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMCustomdrawSliderMic(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnBnClickedCheck1();
    afx_msg void OnBnClickedCheck2();
    afx_msg void OnBnClickedCheck3();
    afx_msg void OnBnClickedCheck4();
    afx_msg void OnBnClickedCheck5();
    afx_msg LONG   OnMCChange(WPARAM wParam, LPARAM lParam);
    afx_msg LONG   OnMLChange(WPARAM wParam, LPARAM lParam);
};


#define GET_MIXER_LINECTR(STH,LINEID)  mixerlinecontrol_##STH.cbStruct = sizeof(MIXERLINECONTROLS); \
    mixerlinecontrol_##STH.dwLineID = LINEID ; \
    mixerlinecontrol_##STH.cControls  = 2;  \
    mixerlinecontrol_##STH.pamxctrl = &mixerControlArray_##STH[0]; \
    mixerlinecontrol_##STH.cbmxctrl = sizeof(MIXERCONTROL) ;\
    mixerGetLineControls((HMIXEROBJ)mixerHandle, &mixerlinecontrol_##STH, MIXER_GETLINECONTROLSF_ALL);
#define GET_CONTROL_DETAIL_VOLUME(STH)  mixerControlDetails_VOLUME_##STH.cbStruct = sizeof(MIXERCONTROLDETAILS); \
    mixerControlDetails_VOLUME_##STH.dwControlID = mixerControlArray_##STH[0].dwControlID; \
    mixerControlDetails_VOLUME_##STH.cChannels = 1;\
    mixerControlDetails_VOLUME_##STH.cMultipleItems = 0;\
    mixerControlDetails_VOLUME_##STH.paDetails = &value_volume_##STH;\
    mixerControlDetails_VOLUME_##STH.cbDetails = sizeof(MIXERCONTROLDETAILS_UNSIGNED);\
    mixerGetControlDetails((HMIXEROBJ)mixerHandle, &mixerControlDetails_VOLUME_##STH, MIXER_GETCONTROLDETAILSF_VALUE);

#define GET_CONTROL_DETAIL_MUTE(STH) mixerControlDetails_MUTE_##STH.cbStruct = sizeof(MIXERCONTROLDETAILS);\
    mixerControlDetails_MUTE_##STH.dwControlID = mixerControlArray_##STH[1].dwControlID;\
    mixerControlDetails_MUTE_##STH.cChannels = 1;\
    mixerControlDetails_MUTE_##STH.cMultipleItems = 0;\
    mixerControlDetails_MUTE_##STH.paDetails = &value_mute_##STH;\
    mixerControlDetails_MUTE_##STH.cbDetails = sizeof(MIXERCONTROLDETAILS_BOOLEAN);\
    mixerGetControlDetails((HMIXEROBJ)mixerHandle, &mixerControlDetails_MUTE_##STH, MIXER_GETCONTROLDETAILSF_VALUE);

#define SET_CTRLDEL_VOLUME(STH,VALUE)    mixerControlDetails_MUTE_##STH.dwControlID = mixerControlArray_##STH[0].dwControlID; \
    mixerControlDetails_MUTE_##STH.cChannels = 1;\
    mixerControlDetails_MUTE_##STH.cMultipleItems = 0;\
    mixerControlDetails_MUTE_##STH.paDetails = &value_volume_##STH;\
    value_volume_##STH.dwValue = VALUE;\
    mixerControlDetails_MUTE_##STH.cbDetails = sizeof(MIXERCONTROLDETAILS_UNSIGNED);\
    mixerSetControlDetails((HMIXEROBJ)mixerHandle, &mixerControlDetails_MUTE_##STH, MIXER_SETCONTROLDETAILSF_VALUE);

// ///set control detail -------volume DWORD
#define SET_CTRLDEL_MUTE(STH,VALUE) mixerControlDetails_MUTE_##STH.dwControlID = mixerControlArray_##STH[1].dwControlID;\
    mixerControlDetails_MUTE_##STH.cChannels = 1;\
    mixerControlDetails_MUTE_##STH.cMultipleItems = 0;\
    mixerControlDetails_MUTE_##STH.paDetails = &value_mute_##STH;\
    value_mute_##STH.fValue = VALUE;\
    mixerControlDetails_MUTE_##STH.cbDetails = sizeof(MIXERCONTROLDETAILS_BOOLEAN);\
    mixerSetControlDetails((HMIXEROBJ)mixerHandle, &mixerControlDetails_MUTE_##STH, MIXER_SETCONTROLDETAILSF_VALUE);


#define SLIDER_INIT(STH)    slider_##STH.SetRange(0,0xffff);\
     
#define SLIDER_SET(STH)   slider_##STH.SetPos((int)value_volume_##STH.dwValue);

#define CHECK_SET(STH)      if(value_mute_##STH.fValue == 1) check_##STH.SetCheck(1); \
    else check_##STH.SetCheck(0);

#define SLIDER_GET(STH)         value_volume_##STH.dwValue=(DWORD)slider_##STH.GetPos();

#define SET_CTRLDEL_VOLUME_SLIDER(STH)    mixerControlDetails_MUTE_##STH.dwControlID = mixerControlArray_##STH[0].dwControlID; \
    mixerControlDetails_MUTE_##STH.cChannels = 1;\
    mixerControlDetails_MUTE_##STH.cMultipleItems = 0;\
    mixerControlDetails_MUTE_##STH.paDetails = &value_volume_##STH;\
    value_volume_##STH.dwValue=(DWORD)slider_##STH.GetPos();\
    mixerControlDetails_MUTE_##STH.cbDetails = sizeof(MIXERCONTROLDETAILS_UNSIGNED);\
    mixerSetControlDetails((HMIXEROBJ)mixerHandle, &mixerControlDetails_MUTE_##STH, MIXER_SETCONTROLDETAILSF_VALUE);

#define SET_CTRLDEL_MUTE_CHECK(STH) mixerControlDetails_MUTE_##STH.dwControlID = mixerControlArray_##STH[1].dwControlID;\
    mixerControlDetails_MUTE_##STH.cChannels = 1;\
    mixerControlDetails_MUTE_##STH.cMultipleItems = 0;\
    mixerControlDetails_MUTE_##STH.paDetails = &value_mute_##STH;\
    value_mute_##STH.fValue =(LONG)check_##STH.GetCheck();\
    mixerControlDetails_MUTE_##STH.cbDetails = sizeof(MIXERCONTROLDETAILS_BOOLEAN);\
    mixerSetControlDetails((HMIXEROBJ)mixerHandle, &mixerControlDetails_MUTE_##STH, MIXER_SETCONTROLDETAILSF_VALUE);
