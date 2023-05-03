#include "GameTextObject.h"


GameTextObject::GameTextObject(std::string text, TTF_Font* font, SDL_Color color, SDL_Rect textDest)
{
	this->m_Text = text;
	this->m_Font = font;
	this->m_FontColor = color;
	this->m_ObjectRect = textDest;
	this->m_Visible = true;

	TTF_SizeText(this->m_Font, this->m_Text.c_str(), &this->m_ObjectRect.w, &this->m_ObjectRect.h);
}

void GameTextObject::Update(GameState* state)
{

}

void GameTextObject::UpdateText(std::string text)
{
	this->UpdateText(text, true);
}

void GameTextObject::UpdateText(std::string text, bool autoResize)
{
	this->m_Text = text;
	
	if(autoResize)
		TTF_SizeText(this->m_Font, this->m_Text.c_str(), &this->m_ObjectRect.w, &this->m_ObjectRect.h);
}

void GameTextObject::UpdatePos(SDL_Rect pos)
{
	this->m_ObjectRect = pos;
}

void GameTextObject::Render(SDL_Renderer* renderer)
{
	if (!this->m_Visible)
		return;

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(this->m_Font, this->m_Text.c_str(), this->m_FontColor);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
	SDL_FreeSurface(surfaceMessage);
	SDL_RenderCopy(renderer, Message, NULL, &this->m_ObjectRect);
}