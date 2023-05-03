#include "Obstacle.h"


Obstacle::Obstacle(GameEnums::ObjectType obstacleType, ObstacleLogicManager* logicMgr, TextureManager* textureMgr)
{
	this->m_ObjectType = obstacleType;
	this->m_ObstacleTexture = textureMgr->Get(obstacleType);
	this->m_LogicComponent = logicMgr->Get(obstacleType);
	this->m_ObjectRect = this->m_LogicComponent->m_ObstaclePos;
	this->m_Visible = true;
	//set default values
	this->m_ObstacleSprite = NULL;
}

Obstacle::Obstacle(GameEnums::ObjectType obstacleType, ObstacleLogicManager* logicMgr, SpriteManager* spriteMgr)
{
	this->m_ObjectType = obstacleType;
	this->m_ObstacleSprite = spriteMgr->Get(obstacleType);
	this->m_LogicComponent = logicMgr->Get(obstacleType);
	this->m_ObjectRect = this->m_LogicComponent->m_ObstaclePos;
	this->m_Visible = true;
	//set default values
	this->m_ObstacleTexture = NULL;
}

Obstacle::~Obstacle()
{

}

void Obstacle::Update(GameState* state)
{
	if (state->m_Paused)
		return;

	this->m_ObjectRect.x -= this->m_LogicComponent->m_Velocity;

	//despawning obstacle
	//if (this->ObjectRect.x <= this->LogicComponent->DespawnOffset)
	//	this->ObjectRect.x = this->LogicComponent->ObstaclePos.x;
}

void Obstacle::Render(SDL_Renderer* renderer)
{
	if (!this->m_Visible)
		return;

	if (this->m_LogicComponent->m_AnimationType == ObstacleAnim::ANIMATED)
	{
		this->m_ObstacleSprite->select_sprite((SDL_GetTicks() / this->m_LogicComponent->m_AnimSpeed) % this->m_LogicComponent->m_FrameCount, 0);
		this->m_ObstacleSprite->draw_selected_sprite(renderer, &this->m_ObjectRect);
	}
	else
		SDL_RenderCopy(renderer, this->m_ObstacleTexture, &this->m_LogicComponent->m_TextureOffset, &this->m_ObjectRect);
}