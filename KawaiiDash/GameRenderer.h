#pragma once
#include "Include/SDL.h"
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <exception>
#include "Player.h"
#include "Obstacle.h"
#include "Utils.h"
#include "GameState.h"
#include "TextureManager.h"
#include "GameDefs.h"
#include "ObstacleManager.h"
#include "ObstacleLogicManager.h"
#include <windows.h>
#include <thread>
#include "GameTextObject.h"
#include "GameTextManager.h"
#include <vector>
#include <format>
#include <sstream>
#include "AudioManager.h"
class GameRenderer
{
	SDL_Window* m_CurrentWindow;
	Mix_Music* BGM;
	SDL_Renderer* m_Renderer;
	SDL_Event m_Evt;
	TextureManager* m_TextureManager;
	SpriteManager* m_SpriteManager;
	ObstacleManager* m_ObstacleManager;
	AudioManager* m_AudioManager;

	std::thread t_tripPlayer;
	std::thread t_spawnObstacles;
	std::thread t_scoreCD;
	std::thread t_pauseDelay;
	std::thread t_invincibilityThread;
	std::thread t_gameStartThread;
	//Game entities

public:
	std::vector<Obstacle*> m_ObstacleVec;
	ObstacleLogicManager* m_ObstacleLogicManager;
	Player* m_CurrentPlayer;
	GameTextManager* m_GameTextManager;
	GameState* m_GameInstance;

	void SetWindowTitle(const char* a);
	GameState* GetGameState();
	void InitRenderer();
	bool CheckCollision(GameObject* a, GameObject* b);
	void SpawnObstacles();
	void Event();
	void Update();
	void Render();
	void Dispose();

};