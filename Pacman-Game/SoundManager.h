#pragma once

#include <string>
#include <map>

#include <D3DX10math.h>

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

	void update(D3DXVECTOR3 const& cameraPos, D3DXVECTOR3 const& cameraForward, D3DXVECTOR3 const& cameraUp);

	void playBackgroundSound(std::string const& filename);
	void playBackgroundSound(std::string const& filename, float volume);
	void playSound(std::string const& filename, D3DXVECTOR3 const& position, float minDistance);
};