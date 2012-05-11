#include "Loop.h"

namespace Sound
{
	Loop::Loop(FMOD::Channel* _channel)
	{
		channel = _channel;
	}

	Loop::~Loop()
	{
		if (channel)
		{
			channel->stop();

			channel = NULL;
		}
	}

	void Loop::setPosition(D3DXVECTOR3 const& _position)
	{
		channel->set3DAttributes(&reinterpret_cast<FMOD_VECTOR const&>(_position), NULL);
	}

	void Loop::setMinDistance(float _distance)
	{
		channel->set3DMinMaxDistance(_distance, 10000.f);
	}

	void Loop::start()
	{
		channel->setPaused(false);
	}

	void Loop::pause()
	{
		channel->setPaused(true);
	}

	void Loop::restart()
	{
		channel->setPosition(0, FMOD_TIMEUNIT_MS);
		start();
	}
}