#include "HID.h"

HID::HID(HWND _hWnd)
{
	m_keyboard = new Keyboard();
	m_mouse = new Mouse(_hWnd);
}

HID::~HID()
{
	m_mouse->~Mouse();
	m_mouse = NULL;

	m_keyboard->~Keyboard();
	m_keyboard = NULL;
}

POINT HID::getMousePos()
{
	m_mousePos = m_mouse->getPos();
	return m_mousePos;
}

bool HID::keyboardKeyDown(char _c)
{
	return m_keyboard->keyDown(_c);
}

bool HID::mouseRightClick()
{
	return m_mouse->buttonClick(MOUSEEVENTF_RIGHTDOWN);
}

bool HID::mouseLeftClick()
{
	return m_mouse->buttonClick(MOUSEEVENTF_LEFTDOWN);
}