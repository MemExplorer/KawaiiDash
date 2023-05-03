#include "GameState.h"

GameState::GameState()
{
	this->Reset();
}

void GameState::Reset()
{
	this->m_HighScore = 0;
	this->GameReset();
}

void GameState::GameReset()
{
	this->m_ScoreCounter = 0;
	this->m_IsRunning = true;
	this->m_GameStarted = false;
	this->m_Paused = false;
	this->m_MaxLives = 3;
	this->m_Lives = 3;
	this->m_PauseRenderer = false;

	//Cooldowns
	this->m_StartCD = false;
	this->m_ScoreCD = false;
	this->m_Invincibility = false;
	this->m_PlayerDeadCD = false;
}

void GameState::IncrementScore()
{
	if (this->m_GameStarted && !this->m_Paused)
		this->m_ScoreCounter++;
}

int GameState::GetScore()
{
	return this->m_ScoreCounter / 5;
}

bool GameState::IsPlayerDead()
{
	return this->m_Lives <= 0;
}