#pragma once
#include <SDL.h>
#include "ObstacleAnimType.h"
#include <map>
#include "ObjectType.h"
#include "ObstacleLogicComponent.h"
#include "Utils.h"
#include "GameDefs.h"

class ObstacleLogicManager
{
	int m_MultiplierCap;
	std::map<GameEnums::ObjectType, ObstacleLogicComponent*> m_ObstacleLogicCompMap;
	void Add(GameEnums::ObjectType objType, ObstacleLogicComponent* obstacle);
	bool In(GameEnums::ObjectType objType);
public:
	int Multiplier;
	ObstacleLogicManager();
	~ObstacleLogicManager();
	ObstacleLogicComponent* Get(GameEnums::ObjectType objType);
	void IncrementVelocity();
	void ResetVelocity();
};

