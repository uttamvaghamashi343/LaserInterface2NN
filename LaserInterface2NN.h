
// LaserInterface2NN.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CLaserInterface2NNApp:
// See LaserInterface2NN.cpp for the implementation of this class
//

class CLaserInterface2NNApp : public CWinApp
{
public:
	CLaserInterface2NNApp();
	~CLaserInterface2NNApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CLaserInterface2NNApp theApp;

