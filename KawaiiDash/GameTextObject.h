#pragma once
#include "GameObject.h"
#include <string>
#include "GameState.h"
#include <SDL_ttf.h>

class GameTextObject : public GameObject
{
	std::string m_Text;
	TTF_Font* m_Font;
	SDL_Color m_FontColor;

public:
	GameTextObject(std::string text, TTF_Font* font, SDL_Color color, SDL_Rect textDest);
	virtual void Update(GameState* state);
	void UpdateText(std::string text);
	void UpdateText(std::string text, bool autoResize);
	void UpdatePos(SDL_Rect pos);
	virtual void Render(SDL_Renderer* renderer);
};

