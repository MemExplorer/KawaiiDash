#include "GameSound.h"
#include <algorithm>
#include <random>

GameSound::GameSound()
{

	this->canPlay = true;
}

GameSound::~GameSound()
{
	for (Mix_Chunk* i : this->m_soundList)
		Mix_FreeChunk(i);

	this->m_soundList.clear();
}

void GameSound::AddSound(const char* sound)
{
	this->m_soundList.push_back(Mix_LoadWAV(sound));
}

void SoundCoolDownThread(GameSound* gSound)
{
	Sleep(1000);
	gSound->canPlay = true;
}

void GameSound::GPlaySound()
{
	this->GPlaySound(false);
}

void GameSound::GPlaySound(bool hasCD)
{
	if (hasCD && !this->canPlay)
		return;

	int randomIndex = 0;
	if (this->m_soundList.size() > 1)
	{
		if (this->m_stackNum.empty())
		{
			//note: std::stack doesn't have an interator
			//generate random numbers in temporary vector
			std::vector<int> tmpVec;
			for (int i = 0; i < this->m_soundList.size(); i++)
				tmpVec.push_back(i);

			std::random_device rd;
			std::mt19937 g(rd());

			//shuffle numbers
			std::shuffle(tmpVec.begin(), tmpVec.end(), g);

			//push all values in stack
			for (int i : tmpVec)
				this->m_stackNum.push(i);

			//clear temp stack
			tmpVec.clear();
		}
		randomIndex = this->m_stackNum.top();
		this->m_stackNum.pop();
	}

	Mix_PlayChannel(-1, this->m_soundList[randomIndex], 0);

	this->canPlay = false;
	
	this->soundThread = std::thread(SoundCoolDownThread, this);
	this->soundThread.detach();
}