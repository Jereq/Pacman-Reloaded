#include "Mouse.h"

Mouse::Mouse(HWND _hWnd)
{
	m_hWnd = _hWnd;
}

Mouse::~Mouse()
{

}

bool Mouse::buttonClick(char _c)
{
	if(GetAsyncKeyState(_c))
	{
		return true;
	}
	return false;
}

POINT Mouse::getPos()
{
	POINT pos;

	GetCursorPos(&pos);

	ScreenToClient(m_hWnd, &pos);

	return pos;
}