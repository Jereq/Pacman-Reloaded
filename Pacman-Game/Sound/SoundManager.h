#pragma once

#include <string>
#include <map>

#include <D3DX10math.h>

#include <boost/shared_ptr.hpp>

#include <fmod/fmod.hpp>
#include <fmod/fmod_errors.h>

namespace Sound
{
	class SoundManager
	{
	private:
		FMOD::System* system;

		void errCheck(FMOD_RESULT const& result);

		typedef std::map<std::string, FMOD::Sound*> sound_map;
		sound_map soundMap;

		FMOD::Sound* backgroundSound;

	public:
		typedef boost::shared_ptr<SoundManager> ptr;

		SoundManager();

		void startup();
		void shutdown();

		void clearCache();

		void update(D3DXVECTOR3 const& cameraPos, D3DXVECTOR3 const& cameraForward, D3DXVECTOR3 const& cameraUp);

		void playBackgroundSound(std::string const& filename);
		void playBackgroundSound(std::string const& filename, float volume);
		void playSound(std::string const& filename, D3DXVECTOR3 const& position, float minDistance);
	};
}