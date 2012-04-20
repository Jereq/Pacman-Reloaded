#include "Keyboard.h"


Keyboard::Keyboard()
{
	/*m_curr = 0;
	m_prev = 0;*/
}

Keyboard::~Keyboard()
{
		
}

bool Keyboard::keyDown(char _c)
{
	if(GetAsyncKeyState(_c))
	{
		return true;
	}
	
	return false;
}

//bool Keyboard::keyPress(char _c)
//{
//	if(GetAsyncKeyState(_c))
//	{
//		m_curr = 1;
//	}
//	else
//	{
//		m_curr = 0;
//	}
//
//	if(m_prev != m_curr)
//	{
//		m_prev = m_curr;
//		return true;
//	}
//
//	return false;
//}