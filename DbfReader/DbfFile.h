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
	char arcLastUpdate[3]; //������ ������Ʈ ��¥.
	uint32_t uNumRecords; //������ ���ڵ� ��
	uint16_t uFirstRecordOffset; // ����� ����Ʈ ��.
	uint16_t uRecordSize;  //���ڵ��� ����Ʈ ��
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
	CStringA Totalrecord; // ��ü ���ڵ� ��
	uint32_t FieldNum; //�ʵ����
	string FieldName; //�ʵ��
	//CStringA FieldName; //�ʵ��
	//int FieldType //�ʵ�Ÿ��
	string NullCheck; // null üũ
	string CheckFieldValue;
	//CStringA NullCheck; // null üũ
};
struct dataSt_2
{
	uint32_t FieldNum; //�ʵ����
	string FieldName; //�ʵ��
	//CStringA FieldName; //�ʵ��
	CStringA FieldValue; // �ڵ� ��
	//uint32_t ValueCnt; // �ڵ��� ���� 
	CStringA ValueCnt; // �ڵ��� ���� 
};
#pragma pack(pop)

class DbfFile_c
{
public:
	DbfFile_c(const char *szFileName);

	//void DumpAll(const char *szDestFileName);
	vector<DbfRecord_s> DumpAll(const char *szDestFileName, bool flag[], map<CString, int> m_DbfDataMap[], int comboIndex, int checkIndex, CString strFileNameParse, CString outputPath, CString outputFileName, bool FileFlag);
	
	vector<pair<int, int>> TotalRecords();

	int DbfFile_c::GetFileAmount(); //���� ���� ��ȯ
	bool DbfFile_c::CheckUpData(CString DbfName, char* FieldName, CString FieldValue); // �ʵ� �� �˼�
	
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