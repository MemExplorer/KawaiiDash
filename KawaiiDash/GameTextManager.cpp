#include "GameTextManager.h"

GameTextManager::GameTextManager()
{
	const char* fontPath = Utils::ResolvePath("Assets/Fonts/upheavtt.ttf");

	this->upheavtt15 = TTF_OpenFont(fontPath, 15);
	this->upheavtt20 = TTF_OpenFont(fontPath, 20);
	this->upheavtt40 = TTF_OpenFont(fontPath, 40);
	SDL_Color darkColor = { 30, 30 , 30 };
	GameTextObject* startScreenMessage = new GameTextObject("Click anywhere to start...", upheavtt20, darkColor, SDL_Rect());
	GameTextObject* scoreTextMessage = new GameTextObject(Utils::Format("Score %06d", 0, 0), upheavtt20, darkColor, SDL_Rect());
	GameTextObject* pauseTextMessage = new GameTextObject("PAUSED", upheavtt40, darkColor, SDL_Rect());
	GameTextObject* deathTextMessage = new GameTextObject("Click anywhere to play again...", upheavtt20, darkColor, SDL_Rect());
	GameTextObject* hiScoreTextMessage = new GameTextObject(Utils::Format("hi %06d", 0, 0), upheavtt20, darkColor, SDL_Rect());
	GameTextObject* controlsTextMessage = new GameTextObject("p - pause | x - exit | space or w - jump", upheavtt15, darkColor, SDL_Rect());

	Utils::GetCenterRect(&startScreenMessage->m_ObjectRect);
	startScreenMessage->m_ObjectRect.y += 30;
	Utils::GetTopRightRect(&scoreTextMessage->m_ObjectRect);
	scoreTextMessage->m_ObjectRect.x -= 10;
	Utils::GetCenterRect(&pauseTextMessage->m_ObjectRect);
	Utils::GetCenterRect(&deathTextMessage->m_ObjectRect);
	Utils::GetTopRightRect(&hiScoreTextMessage->m_ObjectRect);
	hiScoreTextMessage->m_ObjectRect.x -= (20 + scoreTextMessage->m_ObjectRect.w);

	this->Add(GameTextType::START_SCREEN_MESSAGE, startScreenMessage);

	this->Add(GameTextType::SCORE_TEXT_MESSAGE, scoreTextMessage);

	this->Add(GameTextType::PAUSE_TEXT_MESSAGE, pauseTextMessage);

	this->Add(GameTextType::DEATH_TEXT_MESSAGE, deathTextMessage);

	this->Add(GameTextType::HI_SCORE_TEXT_MESSAGE, hiScoreTextMessage);

	this->Add(GameTextType::CONTROLS_TEXT_MESSAGE, controlsTextMessage);
}
GameTextManager::~GameTextManager()
{
	for (auto i : this->gameTextMap)
		delete i.second;

	TTF_CloseFont(this->upheavtt15);
	TTF_CloseFont(this->upheavtt20);
	TTF_CloseFont(this->upheavtt40);
	this->gameTextMap.clear();
}

void GameTextManager::Add(GameTextType::GameTextType textType, GameTextObject* textObject)
{
	if (!this->In(textType))
		this->gameTextMap.insert({ textType, textObject });
}

bool GameTextManager::In(GameTextType::GameTextType textType)
{
	return this->gameTextMap.find(textType) != this->gameTextMap.end();
}

GameTextObject* GameTextManager::Get(GameTextType::GameTextType textType)
{
	return this->gameTextMap.at(textType);
}