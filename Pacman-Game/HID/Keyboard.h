#pragma once

#include <Windows.h>

class Keyboard
{
public:
	Keyboard();
	~Keyboard();

	static void keyDown(WPARAM _wParam);
	static void keyUp(WPARAM _wParam);

	static bool getPressedKey(char _c);
	static bool pressOnce(char _c);

private:
	bool m_keys[256];

	bool m_prevKey[256];
	bool m_currKey[256];
};