#include "stdafx.h"
#include "DbfFile.h"
#include "DbfReaderDlg.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <map>
#include <fstream>
#include <string>
#include <string.h>
#include "locale.h"
#define MAX_SIZE 50
using namespace std;
#pragma warning (disable :4996) 

DbfFile_c::DbfFile_c(const char *szFileName) :
	clFile(szFileName, std::ios_base::binary | std::ios_base::out)
{
	cout << "complited" << endl;
}


vector<pair<int, int>> DbfFile_c::TotalRecords()
{
	vector<pair<int, int>> v;
	clFile.read(reinterpret_cast<char *>(&stHeader), sizeof(stHeader));
	const int numRecords = stHeader.uNumRecords;
	return v;
}

//인코딩 형식 판단 함수 
BOOL IsUTF8Encode(const char * strUrl)
{
	if (NULL == strUrl)
	{
		return FALSE;
	}

	unsigned char * bytes = (unsigned char *)strUrl;
	while (*bytes)
	{
		if ((//ASCII
			bytes[0] == 0x09 ||
			bytes[0] == 0x0A ||
			bytes[0] == 0x0D ||
			(0x20 <= bytes[0] && bytes[0] <= 0x7E)
			)
			)
		{
			bytes += 1;
			continue;
		}
		if ((// non-overlong 2-byte
			(0xC2 <= bytes[0] && bytes[0] <= 0xDF) &&
			(0x80 <= bytes[1] && bytes[1] <= 0xBF)
			)
			)
		{
			bytes += 2;
			continue;
		}
		if ((// excluding overlongs
			bytes[0] == 0xE0 &&
			(0xA0 <= bytes[1] && bytes[1] <= 0xBF) &&
			(0x80 <= bytes[2] && bytes[2] <= 0xBF)
			) ||
			(// straight 3-byte
			((0xE1 <= bytes[0] && bytes[0] <= 0xEC) ||
				bytes[0] == 0xEE ||
				bytes[0] == 0xEF) &&
				(0x80 <= bytes[1] && bytes[1] <= 0xBF) &&
				(0x80 <= bytes[2] && bytes[2] <= 0xBF)
				) ||
				(// excluding surrogates
					bytes[0] == 0xED &&
					(0x80 <= bytes[1] && bytes[1] <= 0x9F) &&
					(0x80 <= bytes[2] && bytes[2] <= 0xBF)
					)
			)
		{
			bytes += 3;
			continue;
		}
		if ((// planes 1-3
			bytes[0] == 0xF0 &&
			(0x90 <= bytes[1] && bytes[1] <= 0xBF) &&
			(0x80 <= bytes[2] && bytes[2] <= 0xBF) &&
			(0x80 <= bytes[3] && bytes[3] <= 0xBF)
			) ||
			(// planes 4-15
			(0xF1 <= bytes[0] && bytes[0] <= 0xF3) &&
				(0x80 <= bytes[1] && bytes[1] <= 0xBF) &&
				(0x80 <= bytes[2] && bytes[2] <= 0xBF) &&
				(0x80 <= bytes[3] && bytes[3] <= 0xBF)
				) ||
				(// planes 16
					bytes[0] == 0xF4 &&
					(0x80 <= bytes[1] && bytes[1] <= 0x8F) &&
					(0x80 <= bytes[2] && bytes[2] <= 0xBF) &&
					(0x80 <= bytes[3] && bytes[3] <= 0xBF)
					)

			) {
			bytes += 4;
			continue;
		}
		return FALSE;
	}
	return TRUE;
}

int DbfFile_c::GetFileAmount()
{
	clFile.read(reinterpret_cast<char *>(&stHeader), sizeof(stHeader));
	const int numRecords = stHeader.uNumRecords;
	return numRecords;
}
void init(map<CString, int> * m_DbfDataMap)
{
	// 필드가 20개 넘어가는 경우가 있어서 50으로 수정함..
	for (int i = 0; i < MAX_SIZE; i++)
	{
		m_DbfDataMap[i].clear();
	}
}

bool CheckUTF8(char * buffer)
{
	int temp = strlen(buffer);
	wchar_t strUnicode[256] = { 0, };
	wchar_t strtempw[10] = { 0, };
	for (int ii = 0; ii < temp; ii++)
	{
		int tempFlagUTF8 = buffer[ii];

		if (tempFlagUTF8 <= -19 && tempFlagUTF8 >= -22)
		{

			char strUTF8[256] = { 0, };
			strcpy_s(strUTF8, 256, &buffer[0]);
			int nLen = MultiByteToWideChar(CP_UTF8, 0, strUTF8, strlen(strUTF8), NULL, NULL);
			MultiByteToWideChar(CP_UTF8, 0, strUTF8, strlen(strUTF8), strUnicode, nLen);
			//utfCheck = true;
			return true;
			break;
		}
		//한글 경우
		else if (tempFlagUTF8 <= -56 && tempFlagUTF8 >= -80)
		{
			//korCheck = true;
			//utfCheck = false;
			return false;
			break;
		}
	}

}

CString ParseStr(int tempFlagUTF8,char * buffer, DbfRecord_s &record)
{
	CString strValue;
	// 숫자 + 문자, 특문 + 문자 경우, 영어 + 문자 경우  
	if ((tempFlagUTF8 <= -19 && tempFlagUTF8 >= -22) || isdigit(buffer[0]) != 0)
	{ //UTF8 Parse
		wchar_t strUnicode[256] = { 0, };
		char strUTF8[256] = { 0, };
		strcpy_s(strUTF8, 256, &buffer[0]);
		int nLen = MultiByteToWideChar(CP_UTF8, 0, strUTF8, strlen(strUTF8), NULL, NULL);
		MultiByteToWideChar(CP_UTF8, 0, strUTF8, strlen(strUTF8), strUnicode, nLen);
		// utfCheck = true;

		//CheckUtfa = isalpha(strUnicode[0]);
		for (int j = 0; j < record.uLength; j++)
		{
			if (strUnicode[j] == '\n')
				break;
			if (strUnicode[j] == ' ')
				continue;
			else
			{
				strValue += &strUnicode[j];
				break;
			}
		}

	}
	else if (tempFlagUTF8 <= -56 && tempFlagUTF8 >= -80)
	{
		// korCheck = true;
		for (int j = 0; j < record.uLength; j++)
		{
			if (buffer[j] == '\n')
				break;
			if (buffer[j] == ' ')
				continue;
			else
			{
				strValue += &buffer[j];
				break;
			}
			//asdf
		}

	}
	else
	{
		wchar_t strUnicode[256] = { 0, };
		char strUTF8[256] = { 0, };
		strcpy_s(strUTF8, 256, &buffer[0]);
		int nLen = MultiByteToWideChar(CP_UTF8, 0, strUTF8, strlen(strUTF8), NULL, NULL);
		MultiByteToWideChar(CP_UTF8, 0, strUTF8, strlen(strUTF8), strUnicode, nLen);
		//CheckUtfa = isalpha(strUnicode[0]);
		for (int j = 0; j < record.uLength; j++)
		{
			if (strUnicode[j] == '\n')
				break;
			if (strUnicode[j] == ' ')
				continue;
			else
			{
				strValue += &strUnicode[j];
				break;
			}

		}
	}

	strValue.Remove(_T(' '));
	//Null check 
	if (strValue == _T(""))
	{
		strValue = "NULL";
	}
	return strValue;
}
vector<DbfRecord_s> DbfFile_c::DumpAll(const char *szDestFileName, bool NullFlag[], map<CString, int> m_DbfDataMap[], int comboIndex,int checkIndex, CString strFileNameParse, CString outputPath, CString outputFileName, bool FileFlag)
{
	locale::global(locale("kor"));
	setlocale(LC_ALL, "");

	//temp VV Linkshape 검증용 
	if (!clFile.good())
	{
		AfxMessageBox(_T("Cannot find Dbf file"));
		throw std::logic_error("Cannot open file");
		return vecRecords;
	}
	/*map 초기화*/
	init(m_DbfDataMap);

	
	clFile.read(reinterpret_cast<char *>(&stHeader), sizeof(stHeader));
	//UTF or ANSI
	bool flagUTF = false;
	CString strCharType = _T("");
	BOOL falgCheckUtf = FALSE;
	bool CheckField[100] = { false, };
	size_t sz = sizeof(DbfRecord_s);
	vector<DbfRecord_s> vecRecords;
	//전체 데이터 갯수 추출
	const int numRecords = stHeader.uNumRecords;
	size_t uTotalBytes = 0;
	size_t uNumRecords = 0;
	std::vector<char> vecBuffer;
	szRowSize = 0;
	szLargestFieldSize = 0;
	int totalRecode = -1;
	CString tempTotalRecode;
	CStringA tempTotalRecodeA;
	CString tempValueCnt;
	CStringA tempValueCntA;
	wchar_t *  tempTotalRecodechar = L"";
	map<CString, int> ::iterator iterMap;

	/*Rodecate 하드코딩 Vector
	//vector<CString> tempRoadVec;*/
	
	//utf-8
	bool utfCheck = false;
	bool korCheck = false; 


	for (unsigned i = 0; i < numRecords; ++i)
	{
		if (numRecords < 0) 
			break;
		char end;
		wchar_t end2;
		clFile.read(&end, 1);
		if (end == 0x0D)
			break;
		if (i == numRecords)
			break;
		vecRecords.push_back(DbfRecord_s());
		DbfRecord_s &record = vecRecords.back();
		memcpy(&record, &end, 1); 
		clFile.read(reinterpret_cast<char *>(&record) + 1, sizeof(DbfRecord_s) - 1);
		szRowSize += record.uLength;
		//TotalRecords();
		ProgressNum = i;
		TotalFiledNum = numRecords;
		CDbfReaderDlg OutWrite;
 
	}


	int minTemp = 987654321;
	int maxTemp = -98765431;

	while (!clFile.eof())
	{
		setlocale(LC_ALL, "");
		locale::global(locale("kor"));
		totalRecode++;
		char deleted;

		vector<CString> tempRecordVec[313];
		clFile.read(&deleted, 1);
		if (deleted == 0x2A)
		{
			clFile.seekg(szRowSize, std::ios_base::cur);
			continue;
		}

		if (clFile.fail())
			break;

		if (deleted == 0x1A) //end-of-file marker
			break;

		int tempsizeaobut = vecRecords.size();

		for (size_t i = 0; i < vecRecords.size(); ++i)
		{
			char buffer[100] = { _T('\n'), };
			//wchar_t buff[100] = { _T('\n'), };
			//tempsizeaobut = vecRecords.size();
			CString strValue = _T("");
			char * contxt = NULL;
			char * tok1 = NULL;
			DbfRecord_s &record = vecRecords[i];
			clFile.read(&buffer[0], record.uLength);


			falgCheckUtf = IsUTF8Encode(&buffer[0]);
			//알파벳 추가.
			//int temssss = buffer[0];
			int CheckUtf = isalpha(buffer[0]);
			int CheckUtfa = isdigit(buffer[0]);
			int tempFlagUTF8 = buffer[0]; //65533이면 ANSI , 아니면 UTF-8 
			/*UTF-8 확인*/
			if (CheckUTF8(buffer))
				korCheck = true; 

			minTemp = min(minTemp, tempFlagUTF8);
			if (tempFlagUTF8 < 0)
				maxTemp = max(tempFlagUTF8, maxTemp);
			
			
			strValue = ParseStr(tempFlagUTF8,buffer,record); 
			tempRecordVec[i].push_back(strValue);


			if (strValue == "NULL")
			{
				NullFlag[i] = true;
			}

			char* FiledName = vecRecords[i].archName;
		 

			if (m_DbfDataMap[i].size() < comboIndex)
			{
				iterMap = m_DbfDataMap[i].find(strValue);
				if (iterMap != m_DbfDataMap[i].end())
				{
					m_DbfDataMap[i].insert(map<CString, int>::value_type(strValue, iterMap->second++));

				}
				else
				{
					m_DbfDataMap[i].insert(map<CString, int>::value_type(strValue, 1));
				}
			}
			MSG msg;
			while (::PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
			{
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}
			uTotalBytes += record.uLength;

		}//end for

	 
	} //end while


	//UTF-8 check z
	if (utfCheck)
		if (korCheck == false)
			strCharType = _T("UTF-8");
		else
			strCharType = _T("ANSI");
	else if (utfCheck == false)
	{
		if (korCheck)
			strCharType = _T("ANSI");
		else
			strCharType = _T("한글없음");
	}
	
	if (FileFlag == false)
	{
		ofstream os(outputPath, ios::out);
		os << "=============================" << endl;
		os << "파일명 : " << CT2A(strFileNameParse) << endl;
		os << "유형 : " << CT2A(strCharType) << endl;
		os << "=============================" << endl;
		//os << "[필드명]\t[필드순서]\t[NullCheck]\t[데이터갯수]" << endl;
		os << "[필드명],[필드순서],[NullCheck],[데이터갯수],[필드값정상적재여부]" << endl;

		for (int i = 0; i < vecRecords.size(); i++)
		{

			dataSt_1 recode;
			//_itow_s(totalRecode, tempTotalRecodechar, 8,10);
			//tempTotalRecode.Format(_T("%d"), totalRecode);
			tempTotalRecode.Format(_T("%d"), m_DbfDataMap[i].size());
			tempTotalRecodeA = tempTotalRecode;
			recode.Totalrecord = tempTotalRecodeA;

			recode.FieldNum = i + 1;
			if (NullFlag[i] == true)
			{
				recode.NullCheck = "NULL";
			}
			else
			{
				recode.NullCheck = "NOT NULL";
			}
			if (CheckField[i])
			{
				recode.CheckFieldValue = "OK";
			}
			else
			{
				recode.CheckFieldValue = "NG";
			}
			recode.FieldName = vecRecords[i].archName;

			
			os << recode.FieldName << "," << recode.FieldNum << "," << recode.NullCheck << "," << recode.Totalrecord << "," << recode.CheckFieldValue << endl;

		}

		os << endl;
		os << "[필드명],[필드순서],[코드명],[코드갯수]" << endl;


		for (int i = 0; i < vecRecords.size(); i++)  //dbf 파일의 갯수 == i
		{
			std::map<CString, int> ::iterator it;

			it = m_DbfDataMap[i].begin();

			for (int j = 0; j < comboIndex; j++)
			{
				dataSt_2 recode;
				recode.FieldNum = i + 1;
				recode.FieldName = vecRecords[i].archName;
				if (it != m_DbfDataMap[i].end())
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
				
				os << recode.FieldName << "," << recode.FieldNum << "," << recode.FieldValue << "," << recode.ValueCnt << endl;
			}
		}
	}
	else
	{
		ofstream os(outputPath, ios::app);
		os << "=============================" << endl;
		os << "파일명 : " << CT2A(strFileNameParse) << endl;
		os << "유형 : " << CT2A(strCharType) << endl;
		os << "=============================" << endl;
		os << "[필드명],[필드순서],[NullCheck],[데이터갯수],[필드값정상적재여부]" << endl;
		for (int i = 0; i < vecRecords.size(); i++)  //dbf 파일의 갯수 == i
		{
			dataSt_1 recode;

			tempTotalRecode.Format(_T("%d"), totalRecode);
			tempTotalRecodeA = tempTotalRecode;
			recode.Totalrecord = tempTotalRecodeA;
			
			recode.FieldNum = i + 1;
			if (NullFlag[i] == true)
			{
				recode.NullCheck = "NULL";
			}
			else
			{
				recode.NullCheck = "NOT NULL";
			}
			if (CheckField[i])
			{
				recode.CheckFieldValue = "OK";
			}
			else
			{
				recode.CheckFieldValue = "NG";
			}
			recode.FieldName = vecRecords[i].archName;

			
			os << recode.FieldName << "," << recode.FieldNum << "," << recode.NullCheck << "," << recode.Totalrecord << "," << recode.CheckFieldValue << endl;


		}

		os << endl;
		os << "[필드명],[필드순서],[코드명],[코드갯수]" << endl;
		for (int i = 0; i < vecRecords.size(); i++)
		{
			std::map<CString, int> ::iterator it;

			it = m_DbfDataMap[i].begin();

			for (int j = 0; j < comboIndex; j++)
			{

				dataSt_2 recode;
				recode.FieldNum = i + 1;
				recode.FieldName = vecRecords[i].archName;


				if (it != m_DbfDataMap[i].end())
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
				os << recode.FieldName << "," << recode.FieldNum << "," << recode.FieldValue << "," << recode.ValueCnt << endl;
			}

		}
		os.close();
	}

	return vecRecords;
}


//


bool DbfFile_c::CheckUpData(CString DbfName, char* FieldName, CString FieldValue)
{


	// dbf이름, 필드명..
	TCHAR path[MAX_PATH]; 
	TCHAR dbfName[_MAX_PATH];
	GetModuleFileName(NULL, path, sizeof path);
	CString striniPath = path;

	int i = striniPath.ReverseFind('\\');
	striniPath = striniPath.Left(i);
	striniPath += _T("\\DbfReader.ini");


	CString ParseFieldName;
	ParseFieldName = (LPSTR)FieldName;

	//LinkShape
	
	GetPrivateProfileString(DbfName, ParseFieldName, _T(""), dbfName, _MAX_PATH, striniPath); 

	//LinkShape_Level를 tok1로 바꿔줌....
	int len = 256;
	char TCharToChar[_MAX_PATH];
	WideCharToMultiByte(CP_ACP, 0, dbfName, len, TCharToChar, len, NULL, NULL);

	bool CheckField = false;
	char *ParceFileValue;
	int ret = 0;
	ParceFileValue = strtok(TCharToChar, ",");
	if (ParceFileValue == NULL)
	{
		CheckField = true;//적재값제한X
		return true;
	}
	while (ParceFileValue != NULL)
	{
		if (ParceFileValue == FieldValue)
		{
			CheckField = true;
			return true;
		}

		//ret += atoi(ParceFileValue);
		ParceFileValue = strtok(NULL, ",");
		//검증 
	}
	if (!CheckField)
		return false; 

	return false;
}