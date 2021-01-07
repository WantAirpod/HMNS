#pragma once
 
#ifndef		__UI_DATA_H__	
#define		__UI_DATA_H__		
using namespace std;

class UI_Data
{
public:
	
	void			init(bool & FileFlag, bool * NullFlag);
	int				GetDirFilesNum(CString& dirName , CString & strFileNameParse);
	CString			SetOutPathName(CString & tempStr);
	CString			GetFileName(CString & filePath);
	CString			SetInputPathParse(CString  inputPath); 
	CString			SetTxtInputPathParse(CString  inputPath);
	CString			JergeOutputPath(bool & OutPathFLag, bool & FullOutPathFLag, CString outputPath, CString tempInputPath);
	CString			GetFileForm(CString & DbfinputPath, CString & POIinputPath);
	bool			CheckDbfFile(CString & inputPath);
	
private : 

};

#endif
