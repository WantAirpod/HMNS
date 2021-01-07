
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
 
struct dataSt_2
{
	//		uint32_t FieldNum; //�ʵ����
	CStringA FieldName; //�ʵ��
						//CStringA FieldName; //�ʵ��
	CStringA FieldValue; // �ڵ� ��
						 //uint32_t ValueCnt; // �ڵ��� ���� 
	CStringA ValueCnt; // �ڵ��� ���� 
};
