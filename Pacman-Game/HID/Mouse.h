#ifndef MOUSE_H
#define MOUSE_H

#include <Windows.h>

class Mouse
{
public:
	Mouse(HWND _hWnd);
	~Mouse();

	bool buttonClick(char _c);

	POINT getPos();

private:

	HWND m_hWnd;
};

#endif