#include "Print.h"


Print::Print()
{

}


Print::~Print()
{

}

void Print::Dbg(const char* arg, ...)
{
	char buf[2048];
	va_list ptr;
	va_start(ptr, arg);
	vsprintf_s(buf, arg, ptr);
	OutputDebugString(buf);
}

bool Print::fatalError(HWND hWnd, LPCSTR msg)
{
	MessageBox(hWnd, msg, "fatal error: ", MB_ICONERROR);
	return false;
}