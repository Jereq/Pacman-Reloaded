#ifndef HID_H
#define HID_H

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
	void keyboardDown(WPARAM _wParam);
	void keyboardUp(WPARAM _wParam);
	bool pressKey(char _c);
	bool pressKeyOnce(char _c);

	bool leftMouseButton();
	bool rightMouseButton();
	bool middleMouseButton();

	POINT getMousePos();

private:
	Keyboard* m_keyboard;
	Mouse* m_mouse;
};

#endif