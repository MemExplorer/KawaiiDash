#pragma once
#include <SDL.h>
#include <map>
#include "Utils.h"
#include "ObjectType.h"
#include "Spritesheet.h"
class TextureManager
{
	std::map<GameEnums::ObjectType, SDL_Texture*> m_TextureMap;
	void Add(GameEnums::ObjectType objType, SDL_Texture* texture);
	bool In(GameEnums::ObjectType objType);
public:

	TextureManager(SDL_Renderer* renderer);
	~TextureManager();
	SDL_Texture* Get(GameEnums::ObjectType objType);

};

