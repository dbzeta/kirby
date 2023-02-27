#include "stdafx.h"
#include "soundManager.h"


soundManager::soundManager()
	: _system(NULL), _sound(NULL), _channel(NULL)
{
}


soundManager::~soundManager()
{
}

HRESULT soundManager::init()
{
	//FMOD 사운드 엔진을 쓰겠다고 선언
	System_Create(&_system);

	_system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, 0);

	_sound = new Sound*[TOTALSOUNDBUFFER];
	_channel = new Channel*[TOTALSOUNDBUFFER];

	memset(_sound, 0, sizeof(Sound*) * (TOTALSOUNDBUFFER));
	memset(_channel, 0, sizeof(Channel*) * (TOTALSOUNDBUFFER));


	return S_OK;
}

void soundManager::release()
{

}

void soundManager::update()
{
	
}

void soundManager::addSound(string keyName, string soundName, bool bgm, bool loop)
{
	arrSoundsIter iter = _mTotalSounds.find(keyName);
	if (iter == _mTotalSounds.end())
	{
		//루프로 재생시킬꺼냐?
		if (loop)
		{
			if (bgm)
			{
				_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);
			}
			else
			{
				_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);
			}
		}
		else //루프가 아니라면
		{
			if (bgm)
			{
				_system->createStream(soundName.c_str(), FMOD_DEFAULT, 0, &_sound[_mTotalSounds.size()]);
			}
			else
			{
				_system->createSound(soundName.c_str(), FMOD_DEFAULT, 0, &_sound[_mTotalSounds.size()]);
			}
		}
		_mTotalSounds.insert(make_pair(keyName, &_sound[_mTotalSounds.size()]));
	}
	else
	{
		if (loop)
		{
			if (bgm)
			{
				_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, 0, iter->second);
			}
			else
			{
				_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, 0, iter->second);
			}
		}
		else //루프가 아니라면
		{
			if (bgm)
			{
				_system->createStream(soundName.c_str(), FMOD_DEFAULT, 0, iter->second);
			}
			else
			{
				_system->createSound(soundName.c_str(), FMOD_DEFAULT, 0, iter->second);
			}
		}
		_mTotalSounds.insert(make_pair(keyName, iter->second));
	}

	//pair<형1, 형2>(변수1, 변수2)
	
}

void soundManager::play(string keyName, float volume) // 0 ~ 255 == 0.0 ~ 1.0f
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		//음악이 있다면
		if (keyName == iter->first)
		{
			_system->playSound(FMOD_CHANNEL_REUSE, *iter->second, false, &_channel[count]);

			_channel[count]->setVolume(volume);
			break;
		}
	}
}

void soundManager::stop(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		//음악이 있다면
		if (keyName == iter->first)
		{
			_channel[count]->stop();
			break;
		}
	}
}

void soundManager::pause(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		//음악이 있다면
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(true);
			break;
		}
	}
}

void soundManager::resume(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		//음악이 있다면
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(false);
			break;
		}
	}
}

float soundManager::getVolume(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;
	float volume = 0.0f;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		//음악이 있다면
		if (keyName == iter->first)
		{
			_channel[count]->getVolume(&volume);
			break;
		}
	}
	return volume;
}

void soundManager::setVolume(string keyName, float volume)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		//음악이 있다면
		if (keyName == iter->first)
		{
			_channel[count]->setVolume(volume);
			break;
		}
	}
}

void soundManager::setPosition(string keyName, unsigned int pos)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPosition(pos, FMOD_TIMEUNIT_MS);
			break;
		}
	}
}

bool soundManager::isPlaySound(string keyName)
{
	bool isPlay;
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->isPlaying(&isPlay);
			break;
		}
	}

	return isPlay;
}

bool soundManager::isPauseSound(string keyName)
{
	bool isPause;
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->getPaused(&isPause);
			break;
		}
	}

	return isPause;
}