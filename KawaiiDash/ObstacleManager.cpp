#include "ObstacleManager.h"


ObstacleManager::ObstacleManager(ObstacleLogicManager* logicMgr, SpriteManager* SpriteMgr, TextureManager* textureMgr)
{
	this->Add(GameEnums::BACKGROUND1, new Obstacle(GameEnums::BACKGROUND1, logicMgr, textureMgr));
	this->Add(GameEnums::BACKGROUND2, new Obstacle(GameEnums::BACKGROUND2, logicMgr, textureMgr));
	this->Add(GameEnums::GAME_TITLE, new Obstacle(GameEnums::GAME_TITLE, logicMgr, SpriteMgr));
	this->Add(GameEnums::TRASHBIN, new Obstacle(GameEnums::TRASHBIN, logicMgr, textureMgr));
	this->Add(GameEnums::DOGGO, new Obstacle(GameEnums::DOGGO, logicMgr, SpriteMgr));
	this->Add(GameEnums::BIRDIE, new Obstacle(GameEnums::BIRDIE, logicMgr, SpriteMgr));
}

ObstacleManager::~ObstacleManager()
{
	for (auto i : this->m_ObstacleMap)
		delete i.second;

	this->m_ObstacleMap.clear();
}

void ObstacleManager::Add(GameEnums::ObjectType objType, Obstacle* obstacle)
{
	if (!this->In(objType))
		this->m_ObstacleMap.insert({ objType, obstacle });
}

Obstacle* ObstacleManager::Get(GameEnums::ObjectType objType)
{
	return this->m_ObstacleMap.at(objType);
}

bool ObstacleManager::In(GameEnums::ObjectType objType)
{
	return this->m_ObstacleMap.find(objType) != this->m_ObstacleMap.end();
}