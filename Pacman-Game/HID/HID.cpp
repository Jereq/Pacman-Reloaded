#include "HID.h"

bool HID::instance = false;
HID* HID::hid = NULL;

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

	instance = false;
}

void HID::input(UINT _msg, WPARAM _wParam)
{
	switch(_msg)
	{
	case WM_KEYDOWN:
		m_keyboard->keyDown(_wParam);
		break;

	case WM_KEYUP:
		m_keyboard->keyUp(_wParam);
		break;
	}
}

bool HID::pressKey(char _c)
{
	if(m_keyboard->getPressedKey(_c) == true) 
	{
		return true;
	}

	return false;
}

bool HID::pressKeyOnce(char _c)
{
	if(m_keyboard->pressOnce(_c) == true)
	{
		return true;
	}

	return false;
}

bool HID::mouseLeftButton()
{
	if(m_mouse->buttonClick(VK_LBUTTON, 0) == true)
	{
		return true;
	}

	return false;
}

bool HID::mouseRightButton()
{
	if(m_mouse->buttonClick(VK_RBUTTON, 1) == true)
	{
		return true;
	}

	return false;
}

bool HID::mouseMiddleButton()
{
	if(m_mouse->buttonClick(VK_MBUTTON, 2) == true)
	{
		return true;
	}

	return false;
}

POINT HID::getMousePos()
{
	return m_mouse->getPos();
}


//Get the instance of the HID
HID* HID::getInstance(HWND _hWnd)
{
	if(!instance)
	{
		hid = new HID(_hWnd);
		instance = true;
		return hid;
	}
	else
	{
		return hid;
	}
}