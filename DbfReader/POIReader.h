#pragma once
#pragma once

#include "stdafx.h" 
#include "DbfFile.h"
#include "DbfReaderDlg.h"
 
using namespace std;

class POIReader
{
public:
	CString		GetFileName(CString & filePath);
	void		UTF8Check(char * inputstr, bool & utfcheck, bool & korCheck);
	void		ParsePOIData(map<CString, int> * m, char * inputstr, wchar_t * strUnicode, bool & NullCheck, bool * NullCheckArr, int & cnt, bool & utfCheck, CString strFileNameParse, bool & LonLat, CString  & strValue, bool & LonCheck, bool & LatCheck);
	void		init();
private:

};

 