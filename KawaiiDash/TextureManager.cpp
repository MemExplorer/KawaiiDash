#include "TextureManager.h"

TextureManager::TextureManager(SDL_Renderer* Renderer)
{
	std::string resolvedPath = Utils::ResolvePath("Assets/Sprites/");
	std::string bgPath = resolvedPath + "GameBG.png";
	std::string heartPath = resolvedPath + "Heart.png";
	std::string shatteredHeartPath = resolvedPath + "shatteredHeart.png";
	std::string trashBinPath = resolvedPath + "trash.png";

	//initialize textures
	SDL_Texture* BG = Utils::LoadTexture(Renderer, bgPath.c_str());
	SDL_Texture* Heart = Utils::LoadTexture(Renderer, heartPath.c_str());
	SDL_Texture* ShatteredHeart = Utils::LoadTexture(Renderer, shatteredHeartPath.c_str());
	this->Add(GameEnums::TRASHBIN, Utils::LoadTexture(Renderer, trashBinPath.c_str()));
	this->Add(GameEnums::BACKGROUND1, BG);
	this->Add(GameEnums::BACKGROUND2, BG);
	this->Add(GameEnums::HEART, Heart);
	this->Add(GameEnums::SHATTERED_HEART, ShatteredHeart);
}

TextureManager::~TextureManager()
{
	for (auto i : this->m_TextureMap)
		SDL_DestroyTexture(i.second);

	this->m_TextureMap.clear();
}

void TextureManager::Add(GameEnums::ObjectType objType, SDL_Texture* texture)
{
	if (!In(objType))
		this->m_TextureMap.insert({ objType, texture });
}

SDL_Texture* TextureManager::Get(GameEnums::ObjectType objType)
{
	return this->m_TextureMap.at(objType);
}


bool TextureManager::In(GameEnums::ObjectType objType)
{
	return this->m_TextureMap.find(objType) != this->m_TextureMap.end();
}
