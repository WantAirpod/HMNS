
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
	/*POI 검증 시*/
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



	//utf관련
	bool utfCheck = false;
	bool korCheck = false;
	/*위경도 관련*/
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

	/*이름파싱*/
	CString strFileNameParse;

	/*전체 txt갯수*/
	int totalFileCount;
};
struct DataSet
{
	CStringA Totalrecord; // 전체 레코드 수
						  //		uint32_t FieldNum; //필드순서
	CStringA FieldName; //필드명
	CStringA nullCheck;

	CStringA FieldValue;
	CStringA ValueCnt; // 코드의 갯수 
					   //CStringA FieldName; //필드명
					   //int FieldType //필드타입
					   //string NullCheck; // null 체크
					   //CStringA NullCheck; // null 체크
};



struct DataSet2
{
	//		uint32_t FieldNum; //필드순서
	CStringA FieldName; //필드명
						//CStringA FieldName; //필드명
	CStringA FieldValue; // 코드 값
						 //uint32_t ValueCnt; // 코드의 갯수 
	CStringA ValueCnt; // 코드의 갯수 
};