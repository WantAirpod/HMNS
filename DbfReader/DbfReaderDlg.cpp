
// DbfReaderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DbfReader.h"
#include "DbfReaderDlg.h"
#include "afxdialogex.h"
#include "POIReader.h"
#include "UI_Data.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CDbfReaderDlg dialog



CDbfReaderDlg::CDbfReaderDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DBFREADER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDbfReaderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BUTTON1, m_PathBtn);
	DDX_Control(pDX, IDC_EDIT1, m_Path);


	DDX_Control(pDX, IDC_EDIT3, m_OptNum);
	DDX_Control(pDX, IDC_PROGRESS1, m_progress);
	DDX_Control(pDX, IDC_TEXT, m_progressText);
	DDX_Control(pDX, IDC_EDIT4, m_outPath);

	DDX_Control(pDX, IDC_BTN_OPENDATA, m_openBtn);
	DDX_Control(pDX, IDC_BTN_OUTPATHOPEN, m_outputpathopen);
	//DDX_Control(pDX, IDC_STATIC_STATE, m_outState);
	//DDX_Control(pDX, IDC_LIST1, m_DbfFileList);
	DDX_Control(pDX, IDC_LIST3, m_DbfFileListCtrl);
	//DDX_Control(pDX, IDC_EDIT2, m_CheckNum);



}

BEGIN_MESSAGE_MAP(CDbfReaderDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()


	ON_BN_CLICKED(m_outputBtn, &CDbfReaderDlg::OnBnClickedoutputbtn)
	ON_BN_CLICKED(IDC_BTN_RUN, &CDbfReaderDlg::OnBnClickedBtnRun)
	ON_BN_CLICKED(m_inputBtn, &CDbfReaderDlg::OnBnClickedinputbtn) 
	ON_BN_CLICKED(IDC_BTN_OPENDATA, &CDbfReaderDlg::OnBnClickedBtnOpendata)
	ON_BN_CLICKED(IDC_BTN_OUTPATHOPEN, &CDbfReaderDlg::OnBnClickedBtnOutpathopen)
END_MESSAGE_MAP()


// CDbfReaderDlg message handlers

BOOL CDbfReaderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//UI_data 선언
	m_pUiData = new UI_Data;
	//POIReader 선언
	m_pPOI = new POIReader;



	//Option 초기 값
	int IniNum = 10;
	CString OptNum;
	OptNum.Format(_T("%d"), IniNum);
	m_OptNum.SetWindowTextW(OptNum);
	//ini 초기값 설정
	TCHAR path[MAX_PATH];
	TCHAR sInput[_MAX_PATH];
	TCHAR sOutput[_MAX_PATH];
	TCHAR sOption[_MAX_PATH]; 


	GetModuleFileName(NULL, path, sizeof path);
	striniPath = path;

	//List 초기 값
	CRect rt;
	m_DbfFileListCtrl.GetWindowRect(&rt);
	m_DbfFileListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_DbfFileListCtrl.InsertColumn(0, TEXT("Number"), LVCFMT_LEFT, rt.Width() *0.1);
	m_DbfFileListCtrl.InsertColumn(1, TEXT("FileName"), LVCFMT_CENTER, rt.Width() *0.3);
	m_DbfFileListCtrl.InsertColumn(2, TEXT("Data"), LVCFMT_CENTER, rt.Width() *0.3);
	m_DbfFileListCtrl.InsertColumn(3, TEXT("Remarks"), LVCFMT_CENTER, rt.Width() *0.3);

	/*ini 설정*/
	int i = striniPath.ReverseFind('\\');
	striniPath = striniPath.Left(i);
	striniPath += _T("\\DbfReader.ini");

	GetPrivateProfileString(_T("DbfReader"), _T("InputPath"), _T(""), sInput, _MAX_PATH, striniPath);
	GetPrivateProfileString(_T("DbfReader"), _T("OutputPath"), _T(""), sOutput, _MAX_PATH, striniPath);
	GetPrivateProfileString(_T("DbfReader"), _T("Option"), _T(""), sOption, _MAX_PATH, striniPath); 
	if (sInput != _T(""))
	{
		m_Path.SetWindowTextW(sInput);
	}

	if (sOutput != _T(""))
	{
		m_outPath.SetWindowTextW(sOutput);

	}

	if (sOption != _T(""))
	{
		m_OptNum.SetWindowTextW(sOption);
	}


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

void CDbfReaderDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDbfReaderDlg::OnPaint()
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
HCURSOR CDbfReaderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


 
void CDbfReaderDlg::OnBnClickedinputbtn()
{ 

	m_DbfData.clear();
	BROWSEINFO BrInfo;
	TCHAR szBuffer[512];// 경로저장 버퍼  
	::ZeroMemory(&BrInfo, sizeof(BROWSEINFO));
	::ZeroMemory(szBuffer, 512); 
	BrInfo.hwndOwner = GetSafeHwnd();
	BrInfo.lpszTitle = _T("폴더를 선택하세요");
	BrInfo.ulFlags = BIF_EDITBOX | BIF_NEWDIALOGSTYLE;//BIF_RETURNONLYFSDIRS || BIF_EDITBOX || TBIF_TEXT || BIF_STATUSTEXT || BIF_VALIDATE; 
	LPITEMIDLIST pItemIdList = ::SHBrowseForFolder(&BrInfo);
	::SHGetPathFromIDList(pItemIdList, szBuffer); 
	inputPath = "";
	inputPath.Format(_T("%s"), szBuffer); 

	/*InputEdit 삽입*/
	CStringA tempStr = CStringA(inputPath);
	char *pChar = tempStr.GetBuffer();
	DbfFile_c file(pChar);
	m_Path.SetWindowTextW(inputPath); 

	tempInputPath = inputPath;
	/*input입력시 자동 output경로 설정*/
	if (tempInputPath != "")
	{ /**/
		m_outPath.SetWindowTextW(m_pUiData->SetOutPathName(tempInputPath));
	}
	/*ListBox 삽입*/
	m_DbfFileListCtrl.DeleteAllItems();
	tempInputPath = inputPath;

	
	
	 
	/*dbf 파일 여부 확인*/
	CFileFind finder;
	CString filepath;
	CString strOutputFileName;
	bool FileFlag = false;
	
	if (m_pUiData->GetFileForm( m_pUiData->SetInputPathParse(tempInputPath), m_pUiData->SetTxtInputPathParse(tempInputPath)) == "DBFFile")
	{
		inputPath = m_pUiData->SetInputPathParse(inputPath);
		FileFormFlag = true;
	}
	else if (m_pUiData->GetFileForm(m_pUiData->SetInputPathParse(tempInputPath), m_pUiData->SetTxtInputPathParse(tempInputPath)) == "POIFile")
	{
		inputPath = m_pUiData->SetTxtInputPathParse(inputPath);
		FileFormFlag = false;
	}
	else 
	{
		MessageBox(_T("파일이 없습니다."));
		return;
	}
	bool working = finder.FindFile(inputPath);
	if (!working)
	{
		MessageBox(_T("파일이 없습니다."));
		return;
	}


	/*ListBox 데이터 삽입*/
	queue<pair<CString, int>> ListQue;  
	while (working)
	{
		CString strData = _T("0");
		int comboIndex;
		working = finder.FindNextFile();
		filepath = finder.GetFilePath();
		//FileName Parse 
		CString strFileNameParse = m_pUiData->GetFileName(filepath);
		CStringA tempStr = CStringA(filepath);
		char *pChar = tempStr.GetBuffer();
		DbfFile_c file(pChar);
		int ListAmout = file.GetFileAmount();
		ListQue.push({ strFileNameParse ,ListAmout });
		Listnum = m_DbfFileListCtrl.GetItemCount();
		CString strr;
		strr.Format(_T("%d"), Listnum);
		CString tempStrList;
		tempStrList.Format(_T("%d"), ListAmout);
		
		if (strFileNameParse.Find(_T("통계")) >= 0)
			continue;
		else
		{
			m_DbfFileListCtrl.InsertItem(Listnum, strr); //숫자,dbf파일이름
			m_DbfFileListCtrl.SetItem(Listnum, 1, LVIF_TEXT, strFileNameParse, NULL, NULL, NULL, NULL); 
		}
		tempStrList.Format(_T("%d"), ListAmout);
		if(FileFormFlag)
			m_DbfFileListCtrl.SetItem(Listnum, 2, LVIF_TEXT, tempStrList, NULL, NULL, NULL, NULL);
	}

 
	
}

 
void CDbfReaderDlg::OnBnClickedoutputbtn()
{ 
	CString szFilter = _T("txt file(*.txt)|*.txt; |ALL File(*.*(|*.*||");
	CFileDialog dlg(FALSE, _T(""), NULL, OFN_OVERWRITEPROMPT || OFN_ENABLESIZING, szFilter); 
	CString strFolder;
	CString strPath;
	CString strFileName;
	CString strFolderPath;
	if (IDOK == dlg.DoModal())
	{
		strFolder = dlg.GetFolderPath();  //L"C:\\Users\\mnsoft\\Desktop\\temp3"	
		outputPath = dlg.GetPathName();  // L"C:\\Users\\mnsoft\\Desktop\\temp3\\99.txt"
		strFileName = dlg.GetFileName(); //99.txt
		m_outPath.SetWindowTextW(outputPath);
	}
}
 

void CDbfReaderDlg::OnBnClickedBtnRun()
{	// TODO: Add your control notification handler code here
	
	CFileFind  cFileFinder;
	CString strOutFileName;
	CString tempOutPath; 
	/*초기화*/
	m_pPOI->init();
	//m_pUiData->init();
	m_Path.GetWindowTextW(inputPath);
	m_outPath.GetWindowTextW(outputPath);
	tempOutPath = outputPath.Mid(0, outputPath.ReverseFind('\\'));
	
	//bool tempOutOutPathFLag = cFileFinder.FindFile(outputPath);

	if (inputPath == "")
	{
		MessageBox(_T("dbf 경로를 입력하세요."));
		return; 
	}
	if (!m_pUiData->CheckDbfFile(inputPath))
	{
		MessageBox(_T(".dbf 파일이 없습니다."));
		inputPath = "";
		outputPath = "";
		return;
	}

	tempInputPath = inputPath;
	/*inputpath 형식변경*/
	//inputPath = m_pUiData->SetInputPathParse(inputPath);   
	m_DbfFileListCtrl.DeleteAllItems();  
	//m_pUiData->SetListBox(inputPath);
	
	if (tempInputPath != "")
	{ /**/
		CString tempStr1 = m_pUiData->SetOutPathName(tempInputPath);
		m_outPath.SetWindowTextW(tempStr1);
	}
	CFileFind finder;
	CString filepath;
	CString strOutputFileName;
	
	//CString FileType;
	bool FileFlag = false;
	
	

	if (m_pUiData->GetFileForm(m_pUiData->SetInputPathParse(tempInputPath), m_pUiData->SetTxtInputPathParse(tempInputPath)) == "DBFFile")
	{
		inputPath = m_pUiData->SetInputPathParse(inputPath);
		FileFormFlag = true;
	}
	else if (m_pUiData->GetFileForm(m_pUiData->SetInputPathParse(tempInputPath), m_pUiData->SetTxtInputPathParse(tempInputPath)) == "POIFile")
	{
		inputPath = m_pUiData->SetTxtInputPathParse(inputPath);
		FileFormFlag = false;
	}
	else
	{
		MessageBox(_T("파일이 없습니다."));
		return;
	}
	bool working = finder.FindFile(inputPath);
	if (!working)
	{
		MessageBox(_T("파일이 없습니다."));
		return;
	}
	/*ListBox 삽입*/
	queue<pair<CString, int>> ListQue; //파일이름,파일갯수
	while (working)
	{
		CString strData = _T("0");
		int comboIndex;
		working = finder.FindNextFile();
		filepath = finder.GetFilePath();
		//FileName Parse 
		strFileNameParse = m_pUiData->GetFileName(filepath); 
		CStringA tempStr = CStringA(filepath);
		char *pChar = tempStr.GetBuffer();
		DbfFile_c file(pChar);
		int ListAmout = file.GetFileAmount();
		ListQue.push({ strFileNameParse ,ListAmout });
		Listnum = m_DbfFileListCtrl.GetItemCount();
		CString strr;
		strr.Format(_T("%d"), Listnum);
		CString tempStrList;
		tempStrList.Format(_T("%d"), ListAmout);  
		if (strFileNameParse.Find(_T("통계")) >= 0)
			continue;
		else
		{
			m_DbfFileListCtrl.InsertItem(Listnum, strr); //숫자,dbf파일이름
			m_DbfFileListCtrl.SetItem(Listnum, 1, LVIF_TEXT, strFileNameParse, NULL, NULL, NULL, NULL);
			totalFileCount++;
		}
		tempStrList.Format(_T("%d"), ListAmout);
		//m_DbfFileListCtrl.SetItem(Listnum, 2, LVIF_TEXT, tempStrList, NULL, NULL, NULL, NULL);
	}
	/* 
	/*output_exception*/
	bool OutPathFLag = cFileFinder.FindFile(tempOutPath);
	bool FullOutPathFLag = cFileFinder.FindFile(outputPath);
	outputPath = m_pUiData->JergeOutputPath(OutPathFLag, FullOutPathFLag, outputPath, tempInputPath);
	if(FileFlag)
		m_outPath.SetWindowTextW(outputPath); 
	/*progress*/ 
	m_progressText.SetWindowTextW(_T("진행중..."));
	m_progress.SetRange(0, 100); 
	if (totalFileCount == 0)
	{
		return;
	}
	int progressNum = 100 / totalFileCount;
	int addProgressNum = 0;
	m_progress.SetPos(progressNum);
 
	//set ini 
	CString iniInputPath;
	CString iniOutputPath;
	CString iniOption;
	m_Path.GetWindowTextW(iniInputPath);
	m_outPath.GetWindowTextW(iniOutputPath);
	m_OptNum.GetWindowTextW(iniOption);

	//Listnum초기화
	Listnum = -1;
	working = finder.FindFile(inputPath);
	while (working)
	{
	
		CString strTotalFileCount;
		CString strFileNameParse;
		CString strData = _T("0");
		CString strData2 = _T("0");

		int comboIndex;
		int checkIndex;

		working = finder.FindNextFile();
		filepath = finder.GetFilePath();
		//FileName Parse
		strFileNameParse = m_pUiData->GetFileName(filepath);
		if (strFileNameParse.Find(_T("통계")) >= 0)
			continue;
		totalFileCount--;
		Listnum++;
		m_progress.SetPos(addProgressNum);
		addProgressNum += progressNum;
		if (addProgressNum >= 100)
			addProgressNum = 100; 
		strTotalFileCount.Format(_T("%d"), addProgressNum);

		
		//set edit
		m_OptNum.GetWindowTextW(strData);
		//m_CheckNum.GetWindowTextW(strData2);
		comboIndex = _ttoi(strData);
		checkIndex = _ttoi(strData2);
		//Path Parse
		CStringA tempStr = CStringA(filepath); 
		CString strTotalRecords;
		CString strProgress; 
		char *pChar = tempStr.GetBuffer(); 

		map<CString, int> m[300];

		/*dbf read*/
		if (FileFormFlag)
		{
			DbfFile_c file(pChar);
			m_DbfData = file.DumpAll(pChar, NullFlag, m_DbfDataMap, comboIndex, checkIndex, strFileNameParse, outputPath, strOutputFileName, FileFlag);
			//list box 삽입
			m_DbfFileListCtrl.SetItem(Listnum, 3, LVIF_TEXT, _T("완료"), NULL, NULL, NULL, NULL);
			file.ProgressNum;
			file.TotalFiledNum;
			strTotalRecords.Format(_T("%d"), file.TotalFiledNum);
		}
		else if (!FileFormFlag)
		{
			CFileException ex;
			CStdioFile rFile;
			ifstream ifFile(filepath, ios::in);
			CString strFileNameParse;

			strFileNameParse = m_pPOI->GetFileName(filepath); 

			rFile.Open(filepath, CFile::modeReadWrite | CFile::typeBinary, &ex);
			 

			int TotalData = 0;
			
			CString m_strPath, str, strValue = _T("");
			CStringA strValueA; 
			CString getFileString;
			
			
			//vector<bool> NullCheckVec;
	
			vector<CString> v;
			map<CString, int> ::iterator iterMap;
			while (!ifFile.eof())
			{
				/*초기화*/
				m_pPOI->init();

				bool NullCheck = false;
				int start = 0;
				int cnt = -1; //map의 갯수 
				TotalData++; //Total 건수  
				bool HDCheck = false;
				char *ptr;
				char inputstr[500000];
				ifFile.getline(inputstr, 500000);

				//////////////////////////////////////////////////////////////////////////////////////////
				//UTF-8 확인
				//////////////////////////////////////////////////////////////////////////////////////////  
				int temp = strlen(inputstr);
				char * tempchar = inputstr;
				wchar_t strUnicode[1024] = { 0, };
				/*UTF-8 체크*/
				m_pPOI->UTF8Check(inputstr, utfCheck, korCheck);

				/*파싱*/
				m_pPOI->ParsePOIData(m, inputstr, strUnicode, NullCheck, NullCheckArr, cnt, utfCheck, strFileNameParse, LonLat, strValue, LonCheck, LatCheck);
				//m_DbfFileListCtrl.SetItem(Listnum, 3, LVIF_TEXT, _T("완료"), NULL, NULL, NULL, NULL);
 
				TurnNum = max(TurnNum, cnt); 

			}

		}

		if (FileFormFlag)
		{
			/*초기화*/
			m_pUiData->init(FileFlag, NullFlag);

			if (finder.IsDots()) continue;

			if (!working)
			{
				m_progress.SetPos(100);
				FileFlag = false;
				m_progressText.SetWindowTextW(_T("100% 완료"));
				WritePrivateProfileString(_T("DbfReader"), _T("InputPath"), iniInputPath, striniPath);
				WritePrivateProfileString(_T("DbfReader"), _T("OutputPath"), iniOutputPath, striniPath);
				WritePrivateProfileString(_T("DbfReader"), _T("Option"), iniOption, striniPath);
				outputPath.Replace(L"\\", L"\\\\");
				openoutputPath = outputPath;
				openoutputDataPath = outputPath;
				openoutputPath = openoutputPath.Mid(0, openoutputPath.ReverseFind('\\'));
				inputPath = "";
				outputPath = "";
			}
			else
			{
				m_progressText.SetWindowTextW(strTotalFileCount + _T("% 완료"));
			}

		}
		else if (!FileFormFlag)
		{ 

			wchar_t FieldName[_MAX_PATH];
			wchar_t tempPath[MAX_PATH];
			CString iniPath;
			CString strFileName;
			strFileName = strFileNameParse;
			GetModuleFileName(NULL, tempPath, sizeof tempPath);
			iniPath = tempPath;

			int i = iniPath.ReverseFind('\\');
			iniPath = striniPath.Left(i);

			iniPath += _T("\\POIReader.ini");
			GetPrivateProfileString(strFileNameParse, _T("FieldName"), _T(""), FieldName, _MAX_PATH, iniPath);
			vector<CString> POI;
			CStringA strValueA;
			CString strValue;
			int start = 0;
			for (int i = 0; i < _MAX_PATH; i++)
			{

				bool checkFirst = false;
				strValueA = _T("");
				strValue = _T("");
				TCHAR TEMPNUMss = FieldName[i];
				if (FieldName[i] == L',')
				{
					checkFirst = true;
					for (int j = start; j < i; j++)
					{
						strValueA += FieldName[j];
						strValue += FieldName[j];

					}
					start = i + 1;
					POI.push_back(strValue);
				}
			}

			//UTF-8 check 
			CString strUTF8Check = _T("");
			if (utfCheck)
				strUTF8Check = _T("UTF-8");
			else if (utfCheck == false)
			{
				if (korCheck)
					strUTF8Check = _T("ANSI");
				else
					strUTF8Check = _T("한글없음");
			}

			CString parseInput = filepath.Mid(0, filepath.ReverseFind('\\'));

			//m_strPath.Replace(L"\\", L"\\\\");
			//CString outputPath = parseInput + _T("\\") + strFileName + _T("통계.txt");
			CString outputPath = parseInput + _T("\\") +_T("통계_") +strFileName ;
			ofstream os(outputPath, ios::out);

			os << "=============================" << endl;
			os << "파일명 : " << CT2A(strFileNameParse) << endl;
			//os << "유형 : " << CT2A(_T("ANSI")) << endl;
			os << "유형 : " << CT2A(strUTF8Check) << endl;
			if (LonLat)
			{
				if (!LonCheck && !LatCheck)
					os << "위경도 값 정상 적재" << endl;
			}
			os << "=============================" << endl;
			//os << "[필드명][필드순서][NullCheck][데이터갯수]" << endl;
			os << "[필드명][NullCheck][데이터갯수]" << endl;

			DataSet DataRecode;
			for (int i = 0; i <= TurnNum; i++)
			{
				DataRecode.FieldName = POI[i];

				//recode.FieldNum = i + 1;
				CString strTotalNum = _T("");
				//strTotalNum.Format(_T("%d"), TotalData);
				strTotalNum.Format(_T("%d"), m[i].size());
				DataRecode.Totalrecord = strTotalNum;
				if (NullCheckArr[i])

					DataRecode.nullCheck = "NULL";
				else
					DataRecode.nullCheck = "NOT NULL";

				//os << recode.FieldName << endl;
				//os << recode.FieldName << "," << recode.FieldNum << "," << recode.NullCheck << "," << recode.Totalrecord << endl;
				os << DataRecode.FieldName << "," << DataRecode.nullCheck << "," << DataRecode.Totalrecord << endl;
			}


			os << endl;
			//os << "[필드명],[필드순서],[코드명],[코드갯수]" << endl;
			os << "[필드명],[코드명],[코드갯수]" << endl;
			std::map<CString, int> ::iterator it;

			for (int i = 0; i <= TurnNum; i++)
			{
				DataSet2 recode;
				it = m[i].begin();

				for (int j = 0; j < 2147000000; j++) //comboNum
				{
					//				recode.FieldNum = i + 1;
					recode.FieldName = POI[i];//vecRecords[i].archName;

					if (it != m[i].end())
					{
						if (it->first == "")
						{
							recode.FieldValue = "NULL";
							tempValueCnt.Format(_T("%d"), it->second);
							tempValueCntA = tempValueCnt;
							recode.ValueCnt = tempValueCntA;

						}
						else
						{

							recode.FieldValue = it->first;
							tempValueCnt.Format(_T("%d"), it->second);
							tempValueCntA = tempValueCnt;
							recode.ValueCnt = tempValueCntA;
						}

						++it;
					}
					else
					{
						break;
					}
					//os << recode.FieldName << "  " << recode.FieldNum << "  " << recode.FieldValue << "  " << recode.ValueCnt << "  " << endl;
					os << recode.FieldName << "," << recode.FieldValue << "," << recode.ValueCnt << endl;
				}
			}

			//MessageBox(_T("완료"));
			
			if (!working)
			{
				m_progress.SetPos(100);
				FileFlag = false;
				m_progressText.SetWindowTextW(_T("100% 완료"));

				WritePrivateProfileString(_T("DbfReader"), _T("InputPath"), iniInputPath, striniPath);
				WritePrivateProfileString(_T("DbfReader"), _T("OutputPath"), iniOutputPath, striniPath);
				WritePrivateProfileString(_T("DbfReader"), _T("Option"), iniOption, striniPath);
				outputPath.Replace(L"\\", L"\\\\");
				openoutputPath = outputPath;
				openoutputDataPath = outputPath;
				openoutputPath = openoutputPath.Mid(0, openoutputPath.ReverseFind('\\'));
				inputPath = "";
				outputPath = "";
			}
			else
			{
				 
				m_progressText.SetWindowTextW(strTotalFileCount + _T("% 완료")); 
				m_progress.SetPos(addProgressNum); 				
				m_DbfFileListCtrl.SetItem(Listnum, 3, LVIF_TEXT, _T("완료"), NULL, NULL, NULL, NULL);
				
			}

		}
		

	}







	// TODO: Add your control notification handler code here// TODO: Add your control notification handler code here
}

void CDbfReaderDlg::OnBnClickedBtnOpendata()
{
	if (openoutputDataPath == "")
	{
		MessageBox(_T("RUN 해주세요."));
		return;
	}
	//openoutputDataPath.Replace(L"\\", L"\\\\");
	// TODO: Add your control notification handler code here
	ShellExecute(NULL, _T("open"), _T("notepad"), openoutputDataPath, NULL, SW_SHOW);


}


void CDbfReaderDlg::OnBnClickedBtnOutpathopen()
{
	if (openoutputPath == "")
	{
		MessageBox(_T("RUN 해주세요."));
		return;
	}
	// TODO: Add your control notification handler code here


	// TODO: Add your control notification handler code here
	//ShellExecute(NULL, _T("open"), _T("notepad"), openinputPath, NULL, SW_SHOW);
	ShellExecute(NULL, _T("open"), openoutputPath, NULL, NULL, SW_SHOW);
}


BOOL CDbfReaderDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		OnBnClickedBtnRun();
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


BOOL CDbfReaderDlg::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Add your specialized code here and/or call the base class
	if (!CDbfReaderDlg::PreCreateWindow(cs))
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style &= ~(WS_THICKFRAME | WS_MAXIMIZEBOX); // 추가 1
	cs.cx = 1000; // 추가 2
	cs.cy = 900; // 추가 3

	return true;
}
