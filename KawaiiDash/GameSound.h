#pragma once
#include <vector>
#include <SDL_mixer.h>
#include "Utils.h"
#include <stack>
#include <windows.h>
#include <thread>

class GameSound
{
	std::vector<Mix_Chunk*> m_soundList;
	std::stack<int> m_stackNum;
	std::thread soundThread;
public:
	bool canPlay;
	GameSound();
	~GameSound();
	void AddSound(const char* sound);
	void GPlaySound();
	void GPlaySound(bool hasCD);
};

