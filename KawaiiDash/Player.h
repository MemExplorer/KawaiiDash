#pragma once
#include "GameObject.h"
#include "Spritesheet.h"
class Player: public GameObject
{
	int m_GravityOrig;
	int m_AnimSpeed;
	int m_SpriteCounter;

	uint8_t m_tripFrameEnd;
public:
	Spritesheet* m_PlayerSprite;
	uint8_t m_tripFrameStart;
	bool m_OnLand;
	bool m_IsJumping;

	Player(Spritesheet* playerSprite, int X, int Y, int Size);
	void Jump();
	void ResetState();
	virtual void Update(GameState* state);
	virtual void Render(SDL_Renderer* renderer);
	void RenderTripped(SDL_Renderer* renderer);
};

