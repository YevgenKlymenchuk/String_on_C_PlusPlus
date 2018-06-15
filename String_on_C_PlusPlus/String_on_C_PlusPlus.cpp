// String_on_C_PlusPlus.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SString.h"



void TestMemoryLeak()
{
	SString s;

	std::wcin >> s;
	s[5] = _T('-');
	std::wcout << _T("What did my typing: [") + s + _T("]");
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	SetConsoleTitle(_T("String tests"));

	TestMemoryLeak();
	_getch();

	_CrtDumpMemoryLeaks();
	return 0;
}

