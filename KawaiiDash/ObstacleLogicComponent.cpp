#include "ObstacleLogicComponent.h"

ObstacleLogicComponent::ObstacleLogicComponent(int velocity, int despawnOffset, SDL_Rect obstaclePos, SDL_Rect textureOffset)
{
	this->m_AnimationType = ObstacleAnim::STILL;
	this->m_Velocity = velocity;
	this->m_OrigVelocity = velocity;
	this->m_ObstaclePos = obstaclePos;

	this->m_TextureOffset = textureOffset;

	this->m_DespawnOffset = despawnOffset;
}

ObstacleLogicComponent::ObstacleLogicComponent(int velocity, int despawnOffset, SDL_Rect obstaclePos, int frameCount, int animSpeed)
{
	this->m_AnimationType = ObstacleAnim::ANIMATED;
	this->m_Velocity = velocity;
	this->m_OrigVelocity = velocity;
	this->m_ObstaclePos = obstaclePos;

	this->m_FrameCount = frameCount;
	this->m_AnimSpeed = animSpeed;

	this->m_DespawnOffset = despawnOffset;
}

void ObstacleLogicComponent::ResetVelocity()
{
	this->m_Velocity = this->m_OrigVelocity;
}