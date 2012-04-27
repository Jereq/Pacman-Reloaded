#ifndef PRINT
#define PRINT

#include <Windows.h>
#include <cstdio>

class Print
{
public:
	Print();
	~Print();

	void	Dbg(const char* arg, ...);
	bool	fatalError(HWND hWnd, LPCSTR msg);
};

#endif

