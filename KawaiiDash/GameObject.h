#pragma once
#include "SDL.h"
#include <exception>
#include "GameState.h"

class GameObject
{

public:
	SDL_Rect m_ObjectRect;
	bool m_Visible;

	virtual void Update(GameState* state)
	{
		throw std::exception("No code implemented!");
	}
	virtual void Render(SDL_Renderer* renderer)
	{
		throw std::exception("No code implemented!");
	}
};

