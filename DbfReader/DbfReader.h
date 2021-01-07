
// DbfReader.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "DbfFile.h"

// CDbfReaderApp:
// See DbfReader.cpp for the implementation of this class
//

class CDbfReaderApp : public CWinApp
{
public:
	CDbfReaderApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CDbfReaderApp theApp;