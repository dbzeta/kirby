#pragma once
#include "singletonBase.h"
#include <map>

#include "inc/fmod.hpp"

#pragma comment (lib, "lib/fmodex_vc.lib")

using namespace FMOD;

#define SOUNDBUFFER 30
#define EXTRACHANNELBUFFER 10

#define TOTALSOUNDBUFFER SOUNDBUFFER + EXTRACHANNELBUFFER

class soundManager : public singletonBase<soundManager>
{
private:
	typedef map<string, Sound**> arrSounds;
	typedef map<string, Sound**>::iterator arrSoundsIter;
	typedef map<string, Channel**> arrChannels;
	typedef map<string, Channel**>::iterator arrChannelsIter;

private:
	System* _system;
	Sound** _sound;
	Channel** _channel;

	arrSounds _mTotalSounds;

public:
	HRESULT init();
	void release();
	void update();

	void addSound(string keyName, string soundName, bool bgm, bool loop);
	void play(string keyName, float volume = 1.0f); // 0 ~ 255 == 0.0 ~ 1.0f
	void stop(string keyName);
	void pause(string keyName);
	void resume(string keyName);

	float getVolume(string keyName);
	void setVolume(string keyName, float volume);

	void setPosition(string keyName, unsigned int pos);

	bool isPlaySound(string keyName);
	bool isPauseSound(string keyName);

	soundManager();
	~soundManager();
};

