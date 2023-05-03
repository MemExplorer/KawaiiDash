#include "Player.h"


Player::Player(Spritesheet* playerSprite, int X, int Y, int Size)
{
	this->m_PlayerSprite = playerSprite;
	SDL_Rect plyRect{};
	plyRect.x = X;
	plyRect.y = Y;
	plyRect.w = Size;
	plyRect.h = Size;

	this->m_IsJumping = false;
	this->m_OnLand = true;
	this->m_ObjectRect = plyRect;
	this->m_Visible = true;
	this->m_SpriteCounter = 0;
	this->m_AnimSpeed = 75;
	this->m_GravityOrig = 5;
	
	this->m_tripFrameStart = 0;
	this->m_tripFrameEnd = 3;
	playerSprite->select_sprite(this->m_SpriteCounter, 0);
     
}

void Player::ResetState()
{
	this->m_IsJumping = false;
	this->m_OnLand = true;
	this->m_ObjectRect.y = 280;
	this->m_tripFrameStart = 0;
}

void Player::Jump()
{
	if (!this->m_IsJumping && this->m_OnLand)
	{
		this->m_IsJumping = true;
		this->m_OnLand = false;
	}
}

void Player::Update(GameState* state)
{
	if (state->m_Paused)
		return;

	if (this->m_IsJumping)
		this->m_ObjectRect.y -= this->m_GravityOrig;
	else
		this->m_ObjectRect.y += this->m_GravityOrig;

	if (this->m_ObjectRect.y >= 280)
	{
		this->m_ObjectRect.y = 280;
		this->m_OnLand = true;
	}

	if (this->m_ObjectRect.y < 100)
		this->m_IsJumping = false;
}

void Player::Render(SDL_Renderer* renderer)
{
	if (!this->m_Visible)
		return;

	if (this->m_OnLand)
	{
		this->m_PlayerSprite->select_sprite((SDL_GetTicks() / this->m_AnimSpeed) % 8, 0);
	}

	this->m_PlayerSprite->draw_selected_sprite(renderer, &this->m_ObjectRect);
}

void Player::RenderTripped(SDL_Renderer* renderer)
{
	if (!this->m_Visible)
		return;
	
	this->m_PlayerSprite->select_sprite(m_tripFrameStart, 1);
	this->m_PlayerSprite->draw_selected_sprite(renderer, &this->m_ObjectRect);
}