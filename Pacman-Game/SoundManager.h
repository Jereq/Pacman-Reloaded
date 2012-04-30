#pragma once

#include <string>
#include <map>

#include <boost/shared_ptr.hpp>

#include <fmod/fmod.hpp>
#include <fmod/fmod_errors.h>

class SoundManager
{
private:
	static FMOD::System* system;

	static void errCheck(FMOD_RESULT const& result);
	static void initSystem();
	static FMOD::System* getSystem();

	typedef std::map<std::string, FMOD::Sound*> sound_map;
	sound_map soundMap;

	FMOD::Sound* backgroundSound;

public:
	typedef boost::shared_ptr<SoundManager> ptr;

	SoundManager();
	~SoundManager();

	static void release();

	void clearCache();

	void update(FMOD_VECTOR const& cameraPos, FMOD_VECTOR const& cameraForward, FMOD_VECTOR const& cameraUp);

	void playBackgroundSound(std::string const& filename);
	void playBackgroundSound(std::string const& filename, float volume);
	void playSound(std::string const& filename, FMOD_VECTOR const& position, float minDistance);
};