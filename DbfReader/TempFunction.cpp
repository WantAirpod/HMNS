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
using namespace std;

void TempFuncLinkShpae() { 
	
	vector<CString> vv[313];
	vector<CString> vv2[313];
	ofstream os("D:\\�˼�\\20201021_LinkShape����\\LinkShape_Lane����TEST_0����2.txt", ios::out);
	os << "[Link_Id],[St_Nd_Id],[Ed_Nd_Id],[Level1],[Length],[St_dir],[Ed_dir],[Link_cate],[Road_cate],[Link_cate2],[VarLane],[Link_facil],[Facil_id],[Facil_Name],[Road_no],[Oneway],[Lane],[Toll],[Car_lane],[Var_lane],[Hov_lane],[S_Hov_lane],[Road_name],[Barrier],[Lane_p],[Lane_n],[Pk_lane_lp],[Pk_lane_ln],[Pk_lane_rp],[Pk_lane_rn],[SpeedLL],[SpeedLH]" << endl;


	/* 
	//Lane_N�� NULL�϶�
	//����<->NULL
	if (vv[25].back() == "NULL")
	{
	//Lane_P�� NULL�� 0�� �ƴ� �� ������
	if (vv[24].back() != "NULL")
	{
	for (int i = 0; i < 32; i++)
	{
	if (i == 25)
	{
	os << "NULL" << "\t";
	continue;
	}
	CT2CA pszConvertedAnsiString(vv[i].back());
	string s(pszConvertedAnsiString);
	os << s << "\t";

	}

	}
	}
	//NULL<->����
	else if (vv[24].back() == "NULL")
	{
	//Lane_P�� NULL�� 0�� �ƴ� �� ������
	if (vv[25].back() != "NULL")
	{
	for (int i = 0; i < 32; i++)
	{
	if (i == 24)
	{
	os << "NULL" << "\t";
	continue;
	}
	CT2CA pszConvertedAnsiString(vv[i].back());
	string s(pszConvertedAnsiString);
	os << s << "\t";

	}

	}
	}
	*/

	//LanmeN�� 0�϶�
	if (vv[25].back() == "0")
	{
		//P�� �����϶�	 
		// ���� <->0
		if ((vv[24].back() != "NULL") && vv[24].back() != "0")
		{
			for (int i = 0; i < 32; i++)
			{
				//vv2[i].push_back(vv[i].back());
				if (i == 25)
				{
					os << "0" << ",";
					continue;
				}
				CT2CA pszConvertedAnsiString(vv[i].back());
				string s(pszConvertedAnsiString);
				os << s << ",";
			}
			os << endl;
		}
	}

	//N�� �����϶� 
	/*
	else if (vv[25].back() != "0" && vv[25].back() != "NULL")
	{
	//if ((vv[24].back() == "NULL") && vv[24].back() != "0")
	//NULL�ΰ��
	if (vv[24].back() == "NULL")
	{
	for (int i = 0; i < 32; i++)
	{
	//vv2[i].push_back(vv[i].back());
	if (i == 25)
	{
	CT2CA pszConvertedAnsiString(vv[25].back());
	string s(pszConvertedAnsiString);
	os << s << "\t";
	}
	CT2CA pszConvertedAnsiString(vv[i].back());
	string s(pszConvertedAnsiString);
	os << s << "\t";
	}
	os << endl;
	}
	*/

	//     0 <-> ����
	else if (vv[24].back() == "0")
	{
		if (vv[25].back() != "0" && vv[25].back() != "NULL")
		{
			for (int i = 0; i < 32; i++)
			{
				//vv2[i].push_back(vv[i].back());
				if (i == 24)
				{
					os << "0" << ",";
					continue;
				}
				CT2CA pszConvertedAnsiString(vv[i].back());
				string s(pszConvertedAnsiString);
				os << s << ",";
			}
			os << endl;
		}

	}


}