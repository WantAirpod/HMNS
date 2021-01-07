
#include "stdafx.h"
#include "UI_Data.h"
#include "DbfFile.h"
#include "DbfReaderDlg.h"



CString UI_Data::SetOutPathName(CString & tempStr)
{
	CString parseInput = tempStr.Mid(tempStr.ReverseFind('\\') + 1, tempStr.GetLength());
	CString outputPath = tempStr + _T("\\") + parseInput + _T(".txt"); 
	return outputPath;
}

CString	UI_Data::GetFileName(CString & filePath)
{
	CString fileNameStr;

	for (int i = filePath.GetLength(); i > 0; i--)
	{
		if (filePath[i] == '\\')
		{
			for (int j = i + 1; j < filePath.GetLength(); j++)
			{
				fileNameStr += filePath[j];
			}
			break;
		}
	}
	return fileNameStr;
}

CString	UI_Data::SetInputPathParse(CString  inputPath)
{
	CString tempStr;
	tempStr = inputPath;
	tempStr.Replace(L"\\", L"\\\\");
	tempStr += L"\\\\*.dbf";
	return tempStr;;
}
CString	UI_Data::SetTxtInputPathParse(CString  inputPath)
{
	CString tempStr;
	tempStr = inputPath;
	tempStr.Replace(L"\\", L"\\\\");
	tempStr += L"\\\\*.txt";
	return tempStr;;
}
CString	UI_Data::GetFileForm(CString & DbfinputPath, CString & POIinputPath)
{
	CString FileFormStr = _T("error");
	CFileFind finder;
 
	if (finder.FindFile(DbfinputPath))
	{
		FileFormStr = _T("DBFFile");
		return FileFormStr;
	}
	else if (finder.FindFile(POIinputPath))
	{
		FileFormStr = _T("POIFile");
		return FileFormStr;
	}

	return FileFormStr;

	
}


CString UI_Data::JergeOutputPath(bool & OutPathFLag, bool & FullOutPathFLag,CString outputPath, CString tempInputPath)
{
	CString errorMessage = _T("output ��θ� Ȯ���ϼ���.");
	if (!FullOutPathFLag && !OutPathFLag)
	{

		//1) �ƿ�ǲ ��� ���Է�, �̻��� ��� �Է� 
		if (outputPath == "" || outputPath.Find(_T("C:\\")) == -1 || outputPath.Find(_T("D:\\")) == -1)
		{
			//qwe
			if (outputPath != ""&&outputPath.Find(_T(".txt")) == -1)
			{
				outputPath = tempInputPath + _T("\\") + outputPath + _T(".txt");
				//m_outPath.SetWindowTextW(outputPath);
				return outputPath;
			}
			//���Է�
			else if (outputPath == "" && outputPath.Find(_T(".txt")) == -1)
			{
				CString parseInput = tempInputPath.Mid(tempInputPath.ReverseFind('\\') + 1, tempInputPath.GetLength());
				outputPath = tempInputPath + _T("\\") + parseInput + _T(".txt");
				//m_outPath.SetWindowTextW(outputPath);
				return outputPath;
			}
			//qwe.txt
			else if (outputPath != "" &&outputPath.Find(_T(".txt")) != -1)
			{
				outputPath = tempInputPath + _T("\\") + outputPath;
				//m_outPath.SetWindowTextW(outputPath);
				return outputPath;
			}

		}
		else
		{
			//MessageBox(_T("output ��θ� Ȯ���ϼ���."));
			return errorMessage;
		}
	}
	if (outputPath.Find(_T("\\")) != -1 && !OutPathFLag && (outputPath.Find(_T("C:\\")) == -1 && outputPath.Find(_T("D:\\")) == -1))
	{ 
		return errorMessage;
	}
	//2) �ƿ�ǲ ��� O, .txt�� �Ⱦ���� 
	if (OutPathFLag && outputPath.Find(_T(".txt")) == -1 && !FullOutPathFLag)
	{

		//CString parseInput = outputPath.Mid(outputPath.ReverseFind('\\') + 1, outputPath.GetLength());
		outputPath = outputPath + _T(".txt");
		//m_outPath.SetWindowTextW(outputPath);
		return outputPath;
	 
	}
	//3) ���ϸ� �Է��� ���
	else if ((outputPath.Find(_T("C:\\")) == -1 && outputPath.Find(_T("D:\\")) == -1))
	{
		if (outputPath.Find(_T(".txt")) == -1)
		{
			outputPath = tempInputPath + _T("\\") + outputPath + _T(".txt");
			return outputPath;
		}
		//4) ���ϸ� + .txt�� �Է��� ���
		else
		{
			outputPath = tempInputPath + _T("\\") + outputPath;
			return outputPath;
		}

	}
	// 5) �ƿ�ǲ ��� ���� 
	else if (FullOutPathFLag)
	{
		//txt ���Է�
		if (outputPath.Find(_T(".txt")) == -1)
		{
			CString parseInput = outputPath.Mid(outputPath.ReverseFind('\\') + 1, outputPath.GetLength());
			outputPath = outputPath + _T("\\") + parseInput + _T(".txt");
			//m_outPath.SetWindowTextW(outputPath);
			return outputPath;
		}
		else
		{
			return outputPath;
			//m_outPath.SetWindowTextW(outputPath);
		}
	}
	return outputPath;
}


int UI_Data::GetDirFilesNum(CString& dirName , CString & strFileNameParse)
{
	int count = 0;
	CFileFind finder;

	BOOL bWorking = finder.FindFile(dirName);

	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		if (finder.IsDots())
		{
			continue;
		}
		 
		count++;

	}
	finder.Close();

	return count;
}


void UI_Data::init(bool & FileFlag, bool * NullFlag)
{
	for (int i = 0; i < 100; i++)
		NullFlag[i] = false;
	FileFlag = true;
}

 

bool UI_Data::CheckDbfFile(CString & inputPath)
{
	CFileFind finder;
	bool working = finder.FindFile(inputPath);
	if (working)
		return true;
	else 
		return true;
}