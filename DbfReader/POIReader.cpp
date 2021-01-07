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


void POIReader::init()
{
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
}

CString	POIReader::GetFileName(CString & filePath)
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


void POIReader::UTF8Check(char * inputstr, bool & utfCheck, bool & korCheck)
{
	int temp = strlen(inputstr);
	char * tempchar = inputstr;
	wchar_t strUnicode[1024] = { 0, };

	for (int ii = 0; ii < temp; ii++)
	{
		int tempFlagUTF8 = inputstr[ii];

		if (tempFlagUTF8 <= -19 && tempFlagUTF8 >= -22)
		{
			char strUTF8[1024] = { 0, };
			strcpy_s(strUTF8, 1024, &inputstr[0]);
			int nLen = MultiByteToWideChar(CP_UTF8, 0, strUTF8, strlen(strUTF8), NULL, NULL);
			MultiByteToWideChar(CP_UTF8, 0, strUTF8, strlen(strUTF8), strUnicode, nLen);
			utfCheck = true;
			break;
		}
		//한글 경우
		else if (tempFlagUTF8 <= -56 && tempFlagUTF8 >= -80)
		{
			korCheck = true;
			break;
		}
	}
}


void POIReader::ParsePOIData(map<CString, int> * m,char * inputstr, wchar_t * strUnicode,bool & NullCheck,bool * NullCheckArr,int & cnt, bool & utfCheck, CString strFileNameParse,bool & LonLat,CString  & strValue, bool & LonCheck , bool & LatCheck)
{
	int temp = strlen(inputstr);
	int start = 0;
	CStringA strValueA;
	map<CString, int> ::iterator iterMap;
	for (int i = 0; i < temp; i++)
	{
		bool checkFirst = false;
		strValueA = _T("");
		//첫번째 짜르기
		if ((inputstr[i] == '\t' && cnt == -1) || (strUnicode[i] == '\t' && cnt == -1))
		{
			checkFirst = true;

			if (utfCheck)
			{
				for (int j = start; j < i; j++)
				{
					strValueA += strUnicode[j];
					//start = j + 2;
				}
			}
			else
			{
				for (int j = start; j < i; j++)
				{
					strValueA += inputstr[j];
					//start = j + 2;
				}
			}

			cnt++;

			strValueA.Remove(_T(' '));
			strValueA.Remove(_T('\"'));
			if (strValueA == "")
			{
				strValueA = "NULL";
				NullCheck = true;
			}

			if (NullCheck)
				NullCheckArr[cnt] = true;
			else
				NullCheckArr[cnt] = false;

			if (strFileNameParse == "POI_XY.txt")
			{
				LonLat = true;
				if (cnt == 6)
				{
					int temp = strValue.GetLength();
					if (strValue.GetLength() != 13)
					{
						LonCheck = true;
					}
				}

				else if (cnt == 7)
				{
					strValue.Remove(_T(' '));
					int tempCnt = 0;
					for (int a = 0; a < strValue.GetLength(); a++)
					{

						wchar_t tempChar = strValue[a];
						if (strValue[a] == '\0')
							break;
						tempCnt++;
					}

					if (tempCnt != 12)
					{
						LatCheck = true;
					}
				}
			}

			strValue = strValueA;
			iterMap = m[cnt].find(strValue);
			if (iterMap != m[cnt].end())
				m[cnt].insert(map<CString, int>::value_type(strValue, iterMap->second++));
			else
				m[cnt].insert(map<CString, int>::value_type(strValue, 1));
			//data.C1 = strValue;
			//v.push_back(strValue);
		}



		if (utfCheck && (strUnicode[i] == '\t' && cnt != -1))
		{
			start = i;
			int w = i;
			strValueA = _T("");
			strValue = _T("");

			while (true)
			{
				w++;
				if (utfCheck)
				{
					if (strUnicode[w] == '\t')
					{
						break;
					}
					if (w > 600)
					{
						w = temp;
						break;
					}
				}
				else
				{
					if (inputstr[w] == '\t')
					{
						break;
					}
					if (w > 600)
					{
						w = temp;
						break;
					}
				}

			}
			if (utfCheck)
			{
				for (int j = start + 1; j < w; j++)
				{
					strValueA += strUnicode[j];
					strValue += strUnicode[j];
				}
			}
			else
			{
				for (int j = start + 1; j < w; j++)
				{
					strValueA += inputstr[j];
				}
			}

			cnt++;
			strValueA.Remove(_T(' '));
			strValueA.Remove(_T('\"'));
			strValue.Remove(_T(' '));
			strValue.Remove(_T('\"'));


			if (utfCheck)
			{
				if (strValue == "")
				{
					strValue = "NULL";
					NullCheckArr[cnt] = true;
				}

			}
			else
			{
				if (strValueA == "")
				{
					strValueA = "NULL";
					NullCheckArr[cnt] = true;
				}
				strValue = strValueA;
			}


			iterMap = m[cnt].find(strValue);
			if (strFileNameParse == "POI_XY.txt")
			{
				LonLat = true;
				if (cnt == 6)
				{
					int temp = strValue.GetLength();
					if (strValue.GetLength() != 13)
					{
						LonCheck = true;
					}
				}

				else if (cnt == 7)
				{
					strValue.Remove(_T(' '));
					int tempCnt = 0;
					for (int a = 0; a < strValue.GetLength(); a++)
					{

						wchar_t tempChar = strValue[a];
						if (strValue[a] == '\0')
							break;
						tempCnt++;
					}

					if (tempCnt != 12)
					{
						LatCheck = true;
					}
				}
			}
			if (iterMap != m[cnt].end())
				m[cnt].insert(map<CString, int>::value_type(strValue, iterMap->second++));
			else
				m[cnt].insert(map<CString, int>::value_type(strValue, 1));
		}
		else if (!utfCheck && (inputstr[i] == '\t' && cnt != -1))
		{
			start = i;
			int w = i;
			strValueA = _T("");
			strValue = _T("");

			while (true)
			{
				w++;
				if (utfCheck)
				{
					if (strUnicode[w] == '\t')
					{
						break;
					}
					if (w > 600)
					{
						w = temp;
						break;
					}
				}
				else
				{
					if (inputstr[w] == '\t')
					{
						break;
					}
					if (w > 600)
					{
						w = temp;
						break;
					}
				}

			}
			if (utfCheck)
			{
				for (int j = start + 1; j < w; j++)
				{
					strValueA += strUnicode[j];
					strValue += strUnicode[j];
				}
			}
			else
			{
				for (int j = start + 1; j < w; j++)
				{
					strValueA += inputstr[j];
					strValue += inputstr[j];
				}
			}

			cnt++;
			strValueA.Remove(_T(' '));
			strValueA.Remove(_T('\"'));
			strValue.Remove(_T(' '));
			strValue.Remove(_T('\"'));

			if (utfCheck)
			{
				if (strValue == "")
				{
					strValue = "NULL";
					NullCheckArr[cnt] = true;
				}

			}
			else
			{
				if (strValueA == "")
				{
					strValueA = "NULL";
					NullCheckArr[cnt] = true;
				}
				strValue = strValueA;
			}


			iterMap = m[cnt].find(strValue);
			if (iterMap != m[cnt].end())
				m[cnt].insert(map<CString, int>::value_type(strValue, iterMap->second++));
			else
				m[cnt].insert(map<CString, int>::value_type(strValue, 1));
		}
	}
	//TurnNum = max(TurnNum, cnt); 


}
 
