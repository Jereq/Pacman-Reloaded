#include "Mouse.h"

Mouse::Mouse(HWND _hWnd)
{
	m_hWnd = _hWnd;
	m_currClick[0] = GetAsyncKeyState(VK_LBUTTON) !=0;
	m_currClick[1] = GetAsyncKeyState(VK_RBUTTON) !=0;
	m_currClick[2] = GetAsyncKeyState(VK_MBUTTON) !=0;
	m_prevClick[0] = false;
	m_prevClick[1] = false;
	m_prevClick[2] = false;
}

Mouse::~Mouse()
{

}

bool Mouse::buttonClick(int _button, UINT _type)
{
	m_prevClick[_type] = m_currClick[_type];
	m_currClick[_type] = GetAsyncKeyState(_button) !=0;

	return !m_prevClick[_type] && m_currClick[_type];
}

POINT Mouse::getPos()
{
	POINT pos;

	GetCursorPos(&pos);

	ScreenToClient(m_hWnd, &pos);

	return pos;
}