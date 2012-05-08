#pragma once

#include "Keyboard.h"
#include "Mouse.h"

class HID
{

private:

	HID(HWND _hWnd);
	Keyboard* m_keyboard;
	Mouse* m_mouse;

	static HID* hid;
	static bool instance;
	

public:
	static HID* getInstance(HWND _hWnd);
	

	~HID();

	void input(UINT _msg, WPARAM _wParam);
	bool pressKey(char _c);
	bool pressKeyOnce(char _c);

	bool mouseLeftButton();
	bool mouseRightButton();
	bool mouseMiddleButton();

	POINT getMousePos();

};