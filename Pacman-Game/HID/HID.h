#pragma once

#include "Keyboard.h"
#include "Mouse.h"

class HID
{
public:
	HID(HWND _hWnd);
	~HID();

	/*Keyboard* getKeyboard();
	Mouse* getMouse();*/

	void input(UINT _msg, WPARAM _wParam);
	bool pressKey(char _c);
	bool pressKeyOnce(char _c);

	bool mouseLeftButton();
	bool mouseRightButton();
	bool mouseMiddleButton();

	POINT getMousePos();

private:
	Keyboard* m_keyboard;
	Mouse* m_mouse;
};