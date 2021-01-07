
// FieldNameConvertorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FieldNameConvertor.h"
#include "FieldNameConvertorDlg.h"
#include "afxdialogex.h"
#include <afxdao.h>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <wchar.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#pragma warning (disable :4996) 
#pragma warning(disable:4995)

using namespace std;
using namespace ADODB;
using namespace ADOX;
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFieldNameConvertorDlg dialog



CFieldNameConvertorDlg::CFieldNameConvertorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FIELDNAMECONVERTOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFieldNameConvertorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_CHECK1, m_Check1);
	//DDX_Control(pDX, IDC_CHECK2, m_Check2);
	DDX_Control(pDX, IDC_EDIT1, m_InputPath);
}

BEGIN_MESSAGE_MAP(CFieldNameConvertorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_BN_CLICKED(IDC_BUTTON1, &CFieldNameConvertorDlg::OnBnClickedButton1)
	//ON_BN_CLICKED(IDC_BUTTON2, &CFieldNameConvertorDlg::OnBnClickedButton2)
	//ON_BN_CLICKED(IDC_BUTTON3, &CFieldNameConvertorDlg::OnBnClickedButton3)
	//ON_BN_CLICKED(IDC_BUTTON4, &CFieldNameConvertorDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CFieldNameConvertorDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CFieldNameConvertorDlg::OnBnClickedButton6)
	//ON_BN_CLICKED(IDC_BUTTON7, &CFieldNameConvertorDlg::OnBnClickedButton7)
END_MESSAGE_MAP()


// CFieldNameConvertorDlg message handlers

BOOL CFieldNameConvertorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFieldNameConvertorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFieldNameConvertorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFieldNameConvertorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//COleVariant�� CString���� ��ȯ���� �Լ�
CString convertString(COleVariant& var)
{
	CString value;
	switch (var.vt)	//COleVariant�� CString���� ����
	{
	case VT_EMPTY:
	case VT_NULL: value = _T("NULL");										break;
	case VT_I2: value.Format(_T("%hd"), V_I2(&var));						break;
	case VT_I4: value.Format(_T("%d"), V_I4(&var));						break;
	case VT_R4: value.Format(_T("%e"), (double)V_R4(&var));				break;
	case VT_R8: value.Format(_T("%e"), V_R8(&var));						break;
	case VT_CY: value = COleCurrency(var).Format();						break;
	case VT_DATE: value = COleDateTime(var).Format(_T("%m %d %y"));			break;
	case VT_BSTR: value = V_BSTRT(&var);									break;
	case VT_DISPATCH: value = _T("VT_DISPATCH");								break;
	case VT_ERROR: value = _T("VT_ERROR");									break;
	case VT_BOOL: V_BOOL(&var) ? value = _T("TRUE") : value = _T("FALSE");		break;
	case VT_VARIANT: value = _T("VT_VARIANT");									break;
	case VT_UNKNOWN: value = _T("VT_UNKNOWN");									break;
	case VT_I1: value = _T("VT_I1");										break;
	case VT_UI1: value.Format(_T("0x%02hX"), (unsigned short)V_UI1(&var));	break;
	case VT_UI2: value = _T("VT_UI2");										break;
	case VT_UI4: value = _T("VT_UI4");										break;
	case VT_I8: value = _T("VT_I8");										break;
	case VT_UI8: value = _T("VT_UI8");										break;
	case VT_INT: value = _T("VT_INT");										break;
	case VT_UINT: value = _T("VT_UINT");									break;
	case VT_VOID: value = _T("VT_VOID");									break;
	case VT_HRESULT: value = _T("VT_HRESULT");									break;
	case VT_PTR: value = _T("VT_PTR");										break;
	case VT_SAFEARRAY: value = _T("VT_SAFEARRAY");								break;
	case VT_CARRAY: value = _T("VT_CARRAY");									break;
	case VT_USERDEFINED: value = _T("VT_USERDEFINED");								break;
	case VT_LPSTR: value = _T("VT_LPSTR");									break;
	case VT_LPWSTR: value = _T("VT_LPWSTR");									break;
	case VT_FILETIME: value = _T("VT_FILETIME");								break;
	case VT_BLOB: value = _T("VT_BLOB");									break;
	case VT_STREAM: value = _T("VT_STREAM");									break;
	case VT_STORAGE: value = _T("VT_STORAGE");									break;
	case VT_STREAMED_OBJECT: value = _T("VT_STREAMED_OBJECT");							break;
	case VT_STORED_OBJECT: value = _T("VT_STORED_OBJECT");							break;
	case VT_BLOB_OBJECT: value = _T("VT_BLOB_OBJECT");								break;
	case VT_CF: value = _T("VT_CF");										break;
	case VT_CLSID: value = _T("VT_CLSID");									break;
	}
	WORD vt = var.vt;
	if (vt & VT_ARRAY)
	{
		vt = vt & ~VT_ARRAY;
		value = _T("Array of ");
	}
	if (vt & VT_BYREF)
	{
		vt = vt & ~VT_BYREF;
		value += _T("Pointer to ");
	}
	if (vt != var.vt)
	{
		switch (vt)
		{
		case VT_EMPTY: value += _T("VT_EMPTY");				break;
		case VT_NULL: value += _T("VT_NULL");				break;
		case VT_I2: value += _T("VT_I2");					break;
		case VT_I4: value += _T("VT_I4");					break;
		case VT_R4: value += _T("VT_R4");					break;
		case VT_R8: value += _T("VT_R8");					break;
		case VT_CY: value += _T("VT_CY");					break;
		case VT_DATE: value += _T("VT_DATE");				break;
		case VT_BSTR: value += _T("VT_BSTR");				break;
		case VT_DISPATCH: value += _T("VT_DISPATCH");			break;
		case VT_ERROR: value += _T("VT_ERROR");				break;
		case VT_BOOL: value += _T("VT_BOOL");				break;
		case VT_VARIANT: value += _T("VT_VARIANT");			break;
		case VT_UNKNOWN: value += _T("VT_UNKNOWN");			break;
		case VT_I1: value += _T("VT_I1");					break;
		case VT_UI1: value += _T("VT_UI1");				break;
		case VT_UI2: value += _T("VT_UI2");				break;
		case VT_UI4: value += _T("VT_UI4");				break;
		case VT_I8: value += _T("VT_I8");					break;
		case VT_UI8: value += _T("VT_UI8");				break;
		case VT_INT: value += _T("VT_INT");				break;
		case VT_UINT: value += _T("VT_UINT");				break;
		case VT_VOID: value += _T("VT_VOID");				break;
		case VT_HRESULT: value += _T("VT_HRESULT");			break;
		case VT_PTR: value += _T("VT_PTR");				break;
		case VT_SAFEARRAY: value += _T("VT_SAFEARRAY");			break;
		case VT_CARRAY: value += _T("VT_CARRAY");				break;
		case VT_USERDEFINED: value += _T("VT_USERDEFINED");		break;
		case VT_LPSTR: value += _T("VT_LPSTR");				break;
		case VT_LPWSTR: value += _T("VT_LPWSTR");				break;
		case VT_FILETIME: value += _T("VT_FILETIME");			break;
		case VT_BLOB: value += _T("VT_BLOB");				break;
		case VT_STREAM: value += _T("VT_STREAM");				break;
		case VT_STORAGE: value += _T("VT_STORAGE");			break;
		case VT_STREAMED_OBJECT: value += _T("VT_STREAMED_OBJECT");	break;
		case VT_STORED_OBJECT: value += _T("VT_STORED_OBJECT");		break;
		case VT_BLOB_OBJECT: value += _T("VT_BLOB_OBJECT");		break;
		case VT_CF: value += _T("VT_CF");					break;
		case VT_CLSID: value += _T("VT_CLSID");				break;
		}
	}
	return value;

}



void CFieldNameConvertorDlg::OnBnClickedButton5()
{
	wchar_t * pMDBPath; 
	CStringW aaa(m_strPath);
	pMDBPath = (wchar_t *)aaa.GetBuffer(); 
	ADOX::_CatalogPtr m_pCatalog = NULL;
	ADOX::_TablePtr m_pTable = NULL;
	ADOX::_ColumnPtr m_pColumn = NULL;
	ADOX::_IndexPtr m_pIndex = NULL;

	/* �� Object�� ���� Instance ����*/
	m_pCatalog.CreateInstance(__uuidof (Catalog));
	m_pTable.CreateInstance(__uuidof (Table));
	m_pIndex.CreateInstance(__uuidof(Index));

	/* ���̺� ����(Chart) */
	for (int i = m_strPath.GetLength(); i > 0; i--)
	{
		if (m_strPath[i] == '\\')
		{
			for (int j = 0; j < i; j++)
			{
				tempStr += m_strPath[j];
			}
			break;
		}
	}
	CString mdbStrtemp; 
	mdbStrtemp = tempStr + _T("mdb");
	wchar_t * databaseStr = mdbStrtemp.GetBuffer(); 

	//file.OpenMDB(L"D:\\�˼�\\20201105mdb��ҹ��ں���");
	CDaoDatabase* database = NULL;
	CDaoDatabase* database2 = NULL;
	CDaoTableDef* tableDef = NULL;
	TCHAR * mdb = _T("");
	mdb = pMDBPath;
	//file.CreateMDB(L"D:\\�˼�\\20201112_mdb��ҹ��ں���_TEMP\\test2.mdb");

	TCHAR * mdb2 = _T("");
	mdb2 = databaseStr;


	//db ����
	database = new CDaoDatabase;
	database->Open(mdb);


	/*���̺� ����*/

	CDaoFieldInfo FT;
	CDaoIndexInfo IT;
	{
		//���̺� ���� Ȯ��
		int tableCnt = database->GetTableDefCount();

		CString strTableCnt;
		CString changStr;//�ӽú���
		strTableCnt.Format(_T("���̺� ���� : %d"), tableCnt);
		//AfxMessageBox(strTableCnt); 

		//��ü ���̺� ��Ϻ���
		CString tableNames;
		for (int i = 0; i < tableCnt; i++)
		{
			//���̺� ���� ��������
			CDaoTableDefInfo tableDefInfo;
			
			CString tempStrName;
			database->GetTableDefInfo(i, tableDefInfo, AFX_DAO_ALL_INFO);	//ù��° ���̺�
			CDaoTableDef TableTest(database);
			if (tableDefInfo.m_lAttributes & dbSystemObject)	//�ý��� ���̺��� ���
			{
				tableNames += _T("�ý��� ���̺� : ");
				if (changStr != "")
				{
					CString queryStr;// �������� ����� ����
					queryStr.Format(
						_T("DROP TABLE ") + changStr
					);
					database->Execute(queryStr);
					changStr = "";
				}
			}


			else
			{

				if (changStr != "")
				{
					CString queryStr;// �������� ����� ����
					queryStr.Format(
						_T("DROP TABLE ") + changStr
					);
					database->Execute(queryStr);
				}
			
				/* �ʵ�� ����... */
				tableDef = new CDaoTableDef(database);
				//tableDef->Open(_T("B_CODE"));	
				tableDef->Open(tableDefInfo.m_strName); //table ���� 
				tempStrName = tableDefInfo.m_strName;
				
				/*�빮�� ����*/ 
				tempStrName.MakeUpper();  
				changStr = tempStrName + _T("ORIGIN");
				tableDef->SetName(changStr);
				//�ʵ� ����
				CDaoFieldInfo fieldInfo;
				CDaoRecordset fie;
				CDaoIndexInfo indexInfo;
				CDaoIndexInfo idxop;
				CDaoIndexFieldInfo fldop;
				int fieldCnt = tableDef->GetFieldCount();
				int tempNumCnt = tableDef->GetIndexCount();

				//���̺� �빮�� ������ ���� 

				TableTest.Create(tempStrName);
				int tempNum = tableDef->GetIndexCount();
				if (tempNum != 0)
				{
					

					tableDef->GetIndexInfo(0, indexInfo);

					idxop.m_strName =indexInfo.m_strName;

					idxop.m_pFieldInfos = &fldop;//indexInfo.m_pFieldInfos;

					idxop.m_nFields = indexInfo.m_nFields;

					idxop.m_bPrimary = TRUE;//indexInfo.m_bPrimary;

					idxop.m_bUnique = indexInfo.m_bUnique;

					idxop.m_bClustered = indexInfo.m_bClustered;

					idxop.m_bIgnoreNulls = indexInfo.m_bIgnoreNulls;

					idxop.m_bRequired = indexInfo.m_bRequired;

					idxop.m_bForeign = indexInfo.m_bForeign;

					idxop.m_lDistinctCount = indexInfo.m_lDistinctCount;

					fldop.m_strName = _T("B_CODE"); // Key field

					fldop.m_bDescending = FALSE; // Ascending 

					

				}



				for (int j = 0; j < fieldCnt; j++)
				{
					//	/*�ʵ� ��ü ����

					tableDef->GetFieldInfo(j, fieldInfo, AFX_DAO_ALL_INFO);


					
					//tableDef->GetIndexInfo(fieldInfo.m_strName, indexInfo);
					
					fieldInfo.m_strName.MakeUpper();
					FT.m_strName = fieldInfo.m_strName;
					FT.m_nType = fieldInfo.m_nType;
					FT.m_lSize = fieldInfo.m_lSize; //������ 50  
					FT.m_lAttributes = fieldInfo.m_lAttributes;
					FT.m_nOrdinalPosition = fieldInfo.m_nOrdinalPosition;
					FT.m_bAllowZeroLength = fieldInfo.m_bAllowZeroLength;
					FT.m_bRequired = fieldInfo.m_bRequired;
					FT.m_lCollatingOrder = fieldInfo.m_lCollatingOrder;
					TableTest.CreateField(FT);
					
					
				}
				TableTest.CreateIndex(idxop);
				TableTest.Append();
		

				//////////////////////////////////////////////////////////////
				//DB���� 
				/////////////////////////////////////////////////////////////
				CDaoQueryDef qd(database);
				//qd.Create()�� ù��° �μ��� ���ڷ� ������ ����Ǹ� qd.Append()�� ������ �Ϸ��.
				//(��������Ǵ� ��ġ�� ������Ʈ�� �����ѵ� �� �𸣰ڽ��ϴ�.)
				//�ѹ����� �ӽ� ������ ��� NULL�� ���� qd.Append()�� �����ָ� �˴ϴ�.
				//qd.Create(_T("JY"), _T("PARAMETERS [binding 1] INT; select * from test_table where 1 = [binding 1]"));
				qd.Create(NULL, _T("PARAMETERS [binding 1] INT; select * from ") + changStr + _T(" where 1 = [binding 1]"));
				//qd.Append();	//�������� ���� ����

				//���ε�
				COleVariant binding1((short)1);
				qd.SetParamValue(_T("[binding 1]"), binding1);

				//INSERT �κ�
				HRESULT hr = S_OK;
				ADODB::_ConnectionPtr m_pConnection;
				//���� �ν��Ͻ� ����
				hr = m_pConnection.CreateInstance(__uuidof(Connection));
				if (SUCCEEDED(hr))
				{
					/* DB ����*/ //�����ʼ� 
					CString tempStr = pMDBPath;
					CString convStr = _T("Provider=Microsoft.Jet.OLEDB.4.0; Data Source=") + tempStr;
					CStringW addStrtemp(convStr);
					wchar_t *addStr = (wchar_t *)addStrtemp.GetBuffer();
					//CString->wchar_t

					m_pConnection->ConnectionString = _bstr_t(addStr);
					
					//m_pConnection->ConnectionString = _bstr_t("Provider=Microsoft.Jet.OLEDB.4.0; Data Source=D:\\�˼�\\20201105mdb��ҹ��ں���\\20201112_mdb��ҹ��ں���_TEMP\\JIBUN_30.mdb");
					//m_pConnection->ConnectionString = _bstr_t("Provider=Microsoft.Jet.OLEDB.4.0; Data Source=D:\\�˼�\\20201112_mdb��ҹ��ں���_TEMP\\COPY_JIBUN11.mdb;");
					m_pConnection->Open("", "", "", adModeUnknown);
				}

				CDaoRecordset rs(database);
				rs.Open(&qd);
				//////////////////////////////////////////////////////////////
				//���� ����
				///////////////////////////////////////////////////////////// 

				while (!rs.IsEOF())
				{
					int cnt = rs.GetFieldCount();
					COleVariant var;
					CString strTemp;
					CString queryStr;// �������� ����� ����
					CString rst;
					CString valueStr;
					for (int i = 0; i < cnt; i++)
					{
						rs.GetFieldValue(i, var);
						rst = convertString(var);
						rst.Trim();
						//rst += _T(", ");
						valueStr += _T("'") + rst + _T("',");
					}
					//rst += _T("\n");
					valueStr = valueStr.Left(valueStr.GetLength() - 1);
					rs.MoveNext();	//scroll
									//���̺� ����
					valueStr.TrimLeft();
					queryStr = _T("INSERT INTO ") + tempStrName + _T(" values"); //���̺��
					queryStr += _T('(') + valueStr + _T(')');
					_bstr_t executeQuery = queryStr;
					/* Ʈ����� ����*/
					m_pConnection->BeginTrans();
					/* "�߰�" ���� ����*/
					m_pConnection->Execute(executeQuery, NULL, adCmdText);
					/* Ʈ����� ����*/
					m_pConnection->CommitTrans();
				}
				qd.Close();

			}



		}//end for
		
		 database->Close();
		 MessageBox(_T("�Ϸ�"));
	 

	}




	//////////////////////////////////////////////////////////////
	//�ʵ� �� ����
	/////////////////////////////////////////////////////////////
	// TODO: Add your control notification handler code here
}



void CFieldNameConvertorDlg::OnBnClickedButton6()
{
	m_InputPath.Clear();
	strFileName = "";
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE, _T("*.mdb"), NULL, OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT, _T("TXT Files(*.mdb)|*.mdb|"), NULL);
	if (dlg.DoModal() == IDOK)
	{
		m_strPath = dlg.GetPathName();
		for (int i = m_strPath.GetLength(); i > 0; i--)
		{
			if (m_strPath[i] == '\\')
			{
				for (int j = i + 1; j < m_strPath.GetLength() - 3; j++)//.mdb����
				{
					strFileNameParse += m_strPath[j];
					strFileName += m_strPath[j];
				}
				break;
			}
		}
	}
	strFileName = strFileName + _T("mdb");
	m_InputPath.SetWindowTextW(strFileName);
}


 