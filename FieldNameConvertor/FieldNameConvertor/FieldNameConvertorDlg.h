
// FieldNameConvertorDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CFieldNameConvertorDlg dialog
class CFieldNameConvertorDlg : public CDialogEx
{
// Construction
public:
	CFieldNameConvertorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FIELDNAMECONVERTOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support



protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	CButton m_Check1;
	CButton m_Check2;
	CEdit m_InputPath;
	afx_msg void OnBnClickedButton6();
	CString m_strPath, tempStr, strValue, strFileNameParse, strFileName = _T("");
	afx_msg void OnBnClickedButton7();
};

// Implementation


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
 
struct dataSt_2
{
	//		uint32_t FieldNum; //필드순서
	CStringA FieldName; //필드명
						//CStringA FieldName; //필드명
	CStringA FieldValue; // 코드 값
						 //uint32_t ValueCnt; // 코드의 갯수 
	CStringA ValueCnt; // 코드의 갯수 
};
