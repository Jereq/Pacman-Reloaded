#include "SoundManager.h"

#include <exception>
#include <sstream>

#include <boost/foreach.hpp>

namespace Sound
{
	SoundManager::ptr SoundManager::instance(new SoundManager);

	FMOD::Sound* SoundManager::getSound(std::string const& filename)
	{
		FMOD_RESULT result;
		if (soundMap.count(filename) == 0)
		{
			result = system->createSound(filename.c_str(), FMOD_3D, NULL, &soundMap[filename]);
			errCheck(result);
		}

		return soundMap[filename];
	}

	FMOD::Sound* SoundManager::getLoopedSound(std::string const& filename)
	{
		FMOD_RESULT result;
		if (loopedSoundMap.count(filename) == 0)
		{
			result = system->createSound(filename.c_str(), FMOD_3D | FMOD_LOOP_NORMAL, NULL, &loopedSoundMap[filename]);
			errCheck(result);
		}

		return loopedSoundMap[filename];
	}

	void SoundManager::errCheck(FMOD_RESULT const& result)
	{
		if (result != FMOD_OK)
		{
			std::ostringstream ostr;
			ostr << "FMOD error ! (" << result << ") " << FMOD_ErrorString(result) << std::endl;
			throw std::exception(ostr.str().c_str());
		}
	}

	SoundManager::SoundManager()
		: backgroundSound(NULL)
	{
	}

	SoundManager::ptr SoundManager::getInstance()
	{
		return instance;
	}

	void SoundManager::startup()
	{
		FMOD_RESULT result;
		unsigned int version;
		int numdrivers;
		FMOD_SPEAKERMODE speakermode;
		FMOD_CAPS caps;
		char name[256];

		/*
		Create a System object and initialize.
		*/
		result = FMOD::System_Create(&system);
		errCheck(result);

		result = system->getVersion(&version);
		errCheck(result);

		if (version < FMOD_VERSION)
		{
			std::ostringstream ostr;
			ostr << "Error! You are using an old version of FMOD " << version << ". This program requires " << FMOD_VERSION << std::endl;
			throw std::exception(ostr.str().c_str());
		}

		result = system->getNumDrivers(&numdrivers);
		errCheck(result);

		if (numdrivers == 0)
		{
			result = system->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
			errCheck(result);
		}
		else
		{
			result = system->getDriverCaps(0, &caps, 0, &speakermode);
			errCheck(result);

			/*
			Set the user selected speaker mode.
			*/
			result = system->setSpeakerMode(speakermode);
			errCheck(result);

			if (caps & FMOD_CAPS_HARDWARE_EMULATED)
			{
				/*
				The user has the 'Acceleration' slider set to off! This is really bad
				for latency! You might want to warn the user about this.
				*/
				result = system->setDSPBufferSize(1024, 10);
				errCheck(result);
			}

			result = system->getDriverInfo(0, name, 256, 0);
			errCheck(result);

			if (strstr(name, "SigmaTel"))
			{
				/*
				Sigmatel sound devices crackle for some reason if the format is PCM 16bit.
				PCM floating point output seems to solve it.
				*/
				result = system->setSoftwareFormat(48000, FMOD_SOUND_FORMAT_PCMFLOAT, 0,0, FMOD_DSP_RESAMPLER_LINEAR);
				errCheck(result);
			}
		}

		result = system->init(100, FMOD_INIT_NORMAL, 0);

		if (result == FMOD_ERR_OUTPUT_CREATEBUFFER)
		{
			/*
			Ok, the speaker mode selected isn't supported by this soundcard. Switch it
			back to stereo...
			*/
			result = system->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
			errCheck(result);

			/*
			... and re-init.
			*/
			result = system->init(100, FMOD_INIT_3D_RIGHTHANDED, 0);
		}
		errCheck(result);
	}

	void SoundManager::shutdown()
	{
		clearCache();

		system->release();
		system = NULL;
	}

	void SoundManager::clearCache()
	{
		if (system)
		{
			BOOST_FOREACH(sound_map::value_type const& entry, soundMap)
			{
				entry.second->release();
			}

			BOOST_FOREACH(sound_map::value_type const& entry, loopedSoundMap)
			{
				entry.second->release();
			}
		}

		soundMap.clear();
		loopedSoundMap.clear();
	}

	void SoundManager::update(D3DXVECTOR3 const& cameraPos, D3DXVECTOR3 const& cameraForward, D3DXVECTOR3 const& cameraUp)
	{
		system->set3DListenerAttributes(0,
			&reinterpret_cast<FMOD_VECTOR const&>(cameraPos), NULL,
			&reinterpret_cast<FMOD_VECTOR const&>(cameraForward),
			&reinterpret_cast<FMOD_VECTOR const&>(cameraUp));
		system->update();
	}

	void SoundManager::playBackgroundSound(std::string const& filename)
	{
		playBackgroundSound(filename, 1.f);
	}

	void SoundManager::playBackgroundSound(std::string const& filename, float volume)
	{
		if (backgroundSound)
		{
			backgroundSound->release();
			backgroundSound = NULL;
		}

		if (filename.empty())
		{
			return;
		}

		FMOD_RESULT result = system->createSound(filename.c_str(), FMOD_LOOP_NORMAL, NULL, &backgroundSound);
		errCheck(result);

		FMOD::Channel* channel = NULL;
		result = system->playSound(FMOD_CHANNEL_FREE, backgroundSound, true, &channel);
		errCheck(result);

		result = channel->setVolume(volume);
		errCheck(result);

		result = channel->setPaused(false);
		errCheck(result);
	}

	void SoundManager::playSound(std::string const& filename, D3DXVECTOR3 const& position, float minDistance)
	{
		FMOD::Sound* sound = getSound(filename);

		FMOD::Channel* channel;
		FMOD_RESULT result = system->playSound(FMOD_CHANNEL_FREE, sound, true, &channel);
		errCheck(result);

		result = channel->set3DAttributes(&reinterpret_cast<FMOD_VECTOR const&>(position), NULL);
		errCheck(result);

		result = channel->set3DMinMaxDistance(minDistance, 10000.f);
		errCheck(result);

		channel->setPaused(false);
	}

	Loop::ptr SoundManager::getLoop(std::string const& filename)
	{
		FMOD::Sound* sound = getLoopedSound(filename);

		FMOD::Channel* channel;
		FMOD_RESULT result = system->playSound(FMOD_CHANNEL_FREE, sound, true, &channel);
		errCheck(result);

		return Loop::ptr(new Loop(channel));
	}
}