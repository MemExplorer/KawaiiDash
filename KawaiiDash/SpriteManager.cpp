#include "SpriteManager.h"

SpriteManager::SpriteManager(SDL_Renderer* Renderer)
{
	std::string resolvedPath = Utils::ResolvePath("Assets/Sprites/");
	std::string playerSpritePath = resolvedPath + "Kawaii Dash Running Girl Sprite Merged.png";
	std::string doggoSpritePath = resolvedPath +"running doggo merged.png";
	std::string birdieSpritePath = resolvedPath + "Birdie.png";
	std::string gameTitlePath = resolvedPath + "kawaii_dash_title_animation_merged.png";
	this->Add(GameEnums::PLAYER, new Spritesheet(Renderer, playerSpritePath.c_str(), 64, 64));
	this->Add(GameEnums::DOGGO, new Spritesheet(Renderer, doggoSpritePath.c_str(), 33, 33));
	this->Add(GameEnums::BIRDIE, new Spritesheet(Renderer, birdieSpritePath.c_str(), 116, 76));
	this->Add(GameEnums::GAME_TITLE, new Spritesheet(Renderer, gameTitlePath.c_str(), 51, 20));
}

SpriteManager::~SpriteManager()
{
	for (auto i : this->m_SpriteMap)
		delete i.second;

	this->m_SpriteMap.clear();
}

void SpriteManager::Add(GameEnums::ObjectType objType, Spritesheet* sprite)
{
	if (!In(objType))
		this->m_SpriteMap.insert({ objType, sprite });
}

Spritesheet* SpriteManager::Get(GameEnums::ObjectType objType)
{
	return this->m_SpriteMap.at(objType);
}

bool SpriteManager::In(GameEnums::ObjectType objType)
{
	return this->m_SpriteMap.find(objType) != this->m_SpriteMap.end();
}