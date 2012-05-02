#pragma once

#include <Windows.h>

class Mouse
{
public:
	Mouse(HWND _hWnd);
	~Mouse();
	
	bool buttonClick(int _button, UINT _type);

	POINT getPos();

private:

	HWND m_hWnd;
	bool m_currClick[3];
	bool m_prevClick[3];
};