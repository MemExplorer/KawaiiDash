#pragma once
#include <map>
#include "ObjectType.h"
#include "Spritesheet.h"
#include "Utils.h"

class SpriteManager
{
	std::map<GameEnums::ObjectType, Spritesheet*> m_SpriteMap;
	void Add(GameEnums::ObjectType objType, Spritesheet* sprite);
	bool In(GameEnums::ObjectType objType);
public:
	SpriteManager(SDL_Renderer* Renderer);
	~SpriteManager();
	Spritesheet* Get(GameEnums::ObjectType objType);
};

