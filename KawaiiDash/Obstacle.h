#pragma once
#include "GameObject.h"
#include "Spritesheet.h"
#include "ObjectType.h"
#include <string>
#include "ObstacleLogicComponent.h"
#include "TextureManager.h"
#include "ObstacleLogicManager.h"
#include "SpriteManager.h"
class Obstacle : public GameObject
{
public:
	SDL_Texture* m_ObstacleTexture;
	GameEnums::ObjectType m_ObjectType;

	//animated properties
	Spritesheet* m_ObstacleSprite;

	//Obstacle Logic
	ObstacleLogicComponent* m_LogicComponent;

	Obstacle(GameEnums::ObjectType obstacleType, ObstacleLogicManager* logicMgr, TextureManager* textureMgr);
	Obstacle(GameEnums::ObjectType obstacleType, ObstacleLogicManager* logicMgr, SpriteManager* textureMgr);
	~Obstacle();
	virtual void Update(GameState* state);
	virtual void Render(SDL_Renderer* renderer);
};

