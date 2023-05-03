#pragma once
#include "Obstacle.h"
#include <map>
#include "TextureManager.h"
#include "GameDefs.h"
class ObstacleManager
{
	std::map< GameEnums::ObjectType, Obstacle*> m_ObstacleMap;
	void Add(GameEnums::ObjectType objType, Obstacle* obstacle);
	bool In(GameEnums::ObjectType objType);
public:
	ObstacleManager(ObstacleLogicManager* logicMgr, SpriteManager* SpriteMgr, TextureManager* textureMgr);
	~ObstacleManager();
	Obstacle* Get(GameEnums::ObjectType objType);
};

