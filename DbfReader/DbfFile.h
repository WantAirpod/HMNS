#pragma once


#ifndef DBF_FILE_H
#define DBF_FILE_H

#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <string>
#include <cstring>


using namespace std;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

struct DbfHeader_s
{
	uint8_t iType;
	char arcLastUpdate[3]; //마지막 업데이트 날짜.
	uint32_t uNumRecords; //파일의 레코드 수
	uint16_t uFirstRecordOffset; // 헤더의 바이트 수.
	uint16_t uRecordSize;  //레코드의 바이트 수
	char uReserved[15];
	uint8_t fFlags; 
	uint8_t uCodePageMark; 
	char uReserved2[2]; 
	 
}; 

#pragma pack(push)
#pragma pack(1)
struct DbfRecord_s
{
	char archName[11];
	char chFieldType;
	uint32_t uDisplacement;
	uint8_t uLength;
	uint8_t uDecimalPlaces;
	uint8_t fFlags;
	uint32_t uNextValue;
	uint8_t uStepValue;
	char uReserved[8];
};

struct dataSt_1
{
	CStringA Totalrecord; // 전체 레코드 수
	uint32_t FieldNum; //필드순서
	string FieldName; //필드명
	//CStringA FieldName; //필드명
	//int FieldType //필드타입
	string NullCheck; // null 체크
	string CheckFieldValue;
	//CStringA NullCheck; // null 체크
};
struct dataSt_2
{
	uint32_t FieldNum; //필드순서
	string FieldName; //필드명
	//CStringA FieldName; //필드명
	CStringA FieldValue; // 코드 값
	//uint32_t ValueCnt; // 코드의 갯수 
	CStringA ValueCnt; // 코드의 갯수 
};
#pragma pack(pop)

class DbfFile_c
{
public:
	DbfFile_c(const char *szFileName);

	//void DumpAll(const char *szDestFileName);
	vector<DbfRecord_s> DumpAll(const char *szDestFileName, bool flag[], map<CString, int> m_DbfDataMap[], int comboIndex, int checkIndex, CString strFileNameParse, CString outputPath, CString outputFileName, bool FileFlag);
	
	vector<pair<int, int>> TotalRecords();

	int DbfFile_c::GetFileAmount(); //파일 갯수 반환
	bool DbfFile_c::CheckUpData(CString DbfName, char* FieldName, CString FieldValue); // 필드 값 검수
	
	void DumpFields(const char *szDestFileName);
	void createDbf(const char *szDestFileName);
	int ProgressNum;
	int TotalFiledNum;
	//	void DbfFile_c::NullCheck(vector<DbfRecord_s>, bool flag[]);

private:
	std::ifstream clFile;


	DbfHeader_s stHeader;

	std::vector<DbfRecord_s> vecRecords;
	size_t szRowSize;
	size_t szLargestFieldSize;

};








#endif