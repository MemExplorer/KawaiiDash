#pragma once
#include <map>
#include "GameTextType.h"
#include "GameTextObject.h"
#include "Utils.h"
class GameTextManager
{
	std::map<GameTextType::GameTextType, GameTextObject*> gameTextMap;
	void Add(GameTextType::GameTextType textType, GameTextObject* textObject);
	bool In(GameTextType::GameTextType textType);
	TTF_Font* upheavtt15;
	TTF_Font* upheavtt20;
	TTF_Font* upheavtt40;
public:
	GameTextManager();
	~GameTextManager();
	GameTextObject* Get(GameTextType::GameTextType textType);
};

