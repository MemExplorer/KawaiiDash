#pragma once
#include <SDL.h>
#include "ObstacleAnimType.h"

class ObstacleLogicComponent
{
public:
	SDL_Rect m_ObstaclePos;
	SDL_Rect m_TextureOffset;
	ObstacleAnim::ObstacleAnimType m_AnimationType;
	int m_Velocity;
	int m_OrigVelocity;
	int m_FrameCount;
	int m_AnimSpeed;

	int m_DespawnOffset;

	ObstacleLogicComponent(int velocity, int despawnOffset, SDL_Rect obstaclePos, SDL_Rect textureOffset);
	ObstacleLogicComponent(int velocity, int despawnOffset, SDL_Rect obstaclePos, int frameCount, int animSpeed);
	void ResetVelocity();
};

