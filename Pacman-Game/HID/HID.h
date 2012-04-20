#ifndef HID_H
#define HID_H

//#include <Windows.h>
#include "Keyboard.h"
#include "Mouse.h"

class HID
{
public:
	HID(HWND _hWnd);
	~HID();

	bool keyboardKeyDown(char _c);

	bool mouseRightClick();
	bool mouseLeftClick();

	POINT getMousePos();
private:
	Keyboard* m_keyboard;
	Mouse* m_mouse;

	POINT m_mousePos;
};

#endif