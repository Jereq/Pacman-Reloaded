#pragma once

#include <boost/shared_ptr.hpp>

#include <fmod/fmod.hpp>
#include <D3DX10math.h>

namespace Sound
{
	class Loop
	{
	private:
		FMOD::Channel* channel;

	public:
		typedef boost::shared_ptr<Loop> ptr;

		Loop(FMOD::Channel* _channel);
		~Loop();

		void setPosition(D3DXVECTOR3 const& _position);
		void setMinDistance(float _distance);

		void start();
		void pause();
		void restart();
	};
}