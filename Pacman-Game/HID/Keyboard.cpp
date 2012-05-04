#include "Keyboard.h"

Keyboard::Keyboard()
{
	for(int i = 0; i < 256; i++)
	{
		m_keys[i] = false;
		m_currKey[i] = false;
		m_prevKey[i] = false;
	}
}

Keyboard::~Keyboard()
{

}

void Keyboard::keyDown(WPARAM _wParam)
{
	m_keys[_wParam] = true;
}

void Keyboard::keyUp(WPARAM _wParam)
{
	m_keys[_wParam] = false;
}

bool Keyboard::getPressedKey(char _c)
{
	return m_keys[_c];
}

bool Keyboard::pressOnce(char _c)
{
	int i;
	i = (int)_c;
	m_prevKey[i] = m_currKey[i];
	m_currKey[i] = m_keys[_c];

	return !m_prevKey[i] && m_currKey[i];
}