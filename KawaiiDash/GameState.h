#pragma once
#include <cstdint>
class GameState
{
public:
	bool m_IsRunning;
	bool m_GameStarted;
	bool m_Paused;
	uint32_t m_ScoreCounter;
	uint32_t m_HighScore;
	uint8_t m_Lives;
	uint8_t m_MaxLives;
	bool m_PauseRenderer;

	bool m_StartCD;
	bool m_ScoreCD;
	bool m_Invincibility;
	bool m_PlayerDeadCD;

	GameState();

	void Reset();
	void GameReset();

	void IncrementScore();
	int GetScore();
	bool IsPlayerDead();
};

