#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <Windows.h>

class Keyboard
{
public:
	Keyboard();
	~Keyboard();

	void keyDown(WPARAM _wParam);
	void keyUp(WPARAM _wParam);

	bool getPressedKey(char _c);
	bool pressOnce(char _c);

private:

	bool m_keys[256];

	bool m_prevKey[256];
	bool m_currKey[256];
};

#endif