#pragma once
#include <map>
#include "GameSoundType.h"
#include "GameSound.h"


class AudioManager
{
	std::map<GameSoundType::GameSoundType, GameSound*> m_gameSoundMap;
	void Add(GameSoundType::GameSoundType soundType, GameSound* gameSound);
	bool In(GameSoundType::GameSoundType soundType);
public:
	AudioManager();
	~AudioManager();
	void GPlaySound(GameSoundType::GameSoundType soundType);
	void GPlaySound(GameSoundType::GameSoundType soundType, bool hasCD);
};

