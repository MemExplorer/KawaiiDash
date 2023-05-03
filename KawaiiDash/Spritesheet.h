#pragma once

#include "Include/SDL.h"
#include "Include/SDL_image.h"
class Spritesheet
{
public:
    Spritesheet(SDL_Renderer* renderer, char const* path, int width, int height);
    ~Spritesheet();

    void select_sprite(int x, int y);
    void draw_selected_sprite(SDL_Renderer* renderer, SDL_Rect* position);

private:
    SDL_Rect     m_clip;
    SDL_Texture* m_spritesheet_image;

    int m_start_x;
    int m_start_y;
};