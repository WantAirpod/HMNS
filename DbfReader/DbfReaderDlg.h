
// DbfReaderDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include <queue>
#include "UI_Data.h"
#include "POIReader.h"
#define MAX_PATH          260


// CDbfReaderDlg dialog
class CDbfReaderDlg : public CDialogEx
{
// Construction
public:
	
	CDbfReaderDlg(CWnd* pParent = NULL);	// standard constructor
	UI_Data	 *	m_pUiData;
	POIReader * m_pPOI;

	CStatic m_outState;
	void SetState(int i, int numRecords)
	{
		CString strOutState;
		CString strTotalState;
		strOutState.Format(_T("%d"), i);
		strTotalState.Format(_T("%d"), numRecords);
		m_outState.SetWindowTextW(strOutState + "/" + strTotalState );
		// m_OptNum.SetWindowTextW(strOutState + "/" + strTotalState);
		
	}
 
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DBFREADER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_ComboOpt;
	vector<DbfRecord_s> m_DbfData;
	map<CString, int> m_DbfDataMap[100];
	bool NullFlag[100];
	CButton m_PathBtn; 
	CEdit m_Path; 
	CString inputPath; //CString m_strinputPath;
	CString inputTxtPathStr;
	CString tempInputPath; // CString 
	CString outputPath;
	CString openoutputPath;
	CString openoutputDataPath; 
	CString striniPath; 
	CEdit m_OptNum;
	
	CProgressCtrl m_progress;
	CStatic m_progressText;
	/*POI ���� ��*/
	bool CheckPOI;
	CEdit m_outPath;
	//CButton IDC_BTN_RUN;
	afx_msg void OnBnClickedinputbtn();
	afx_msg void OnBnClickedoutputbtn();
	afx_msg void OnBnClickedBtnRun(); 
	CButton m_openBtn;
	afx_msg void OnBnClickedBtnOpendata();
	CButton m_outputpathopen;
	afx_msg void OnBnClickedBtnOutpathopen();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs); 
	//CListBox m_DbfFileList;
	CListCtrl m_DbfFileListCtrl;
	int Listnum = 0;
	//CEdit m_CheckNum;



	//utf����
	bool utfCheck = false;
	bool korCheck = false;
	/*���浵 ����*/
	bool LonCheck = false;
	bool LatCheck = false;
	bool LonLat = false;

	/*total*/
	int TurnNum;

	/*null check*/
	bool NullCheckArr[50] = { false, };

	/**/
	CString tempValueCnt;
	CStringA tempValueCntA;

	/*POI & DBF File Format*/
	bool FileFormFlag = false;

	/*�̸��Ľ�*/
	CString strFileNameParse;

	/*��ü txt����*/
	int totalFileCount;
};
struct DataSet
{
	CStringA Totalrecord; // ��ü ���ڵ� ��
						  //		uint32_t FieldNum; //�ʵ����
	CStringA FieldName; //�ʵ��
	CStringA nullCheck;

	CStringA FieldValue;
	CStringA ValueCnt; // �ڵ��� ���� 
					   //CStringA FieldName; //�ʵ��
					   //int FieldType //�ʵ�Ÿ��
					   //string NullCheck; // null üũ
					   //CStringA NullCheck; // null üũ
};



struct DataSet2
{
	//		uint32_t FieldNum; //�ʵ����
	CStringA FieldName; //�ʵ��
						//CStringA FieldName; //�ʵ��
	CStringA FieldValue; // �ڵ� ��
						 //uint32_t ValueCnt; // �ڵ��� ���� 
	CStringA ValueCnt; // �ڵ��� ���� 
};