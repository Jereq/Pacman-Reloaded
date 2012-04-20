#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <Windows.h>

class Keyboard
{
public:
	Keyboard();
	~Keyboard();

	void update();

	bool keyDown(char _c);

	//bool keyPress(char _c);

private:
	//int m_curr, m_prev;
};

#endif