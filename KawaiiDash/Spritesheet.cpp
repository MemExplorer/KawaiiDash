#include "spritesheet.h"

Spritesheet::Spritesheet(SDL_Renderer* renderer, char const* path, int width, int height)
{
    SDL_Surface* surface = IMG_Load(path);
    m_spritesheet_image = SDL_CreateTextureFromSurface(renderer, surface);

    m_clip.w = width;
    m_clip.h = height;
    SDL_FreeSurface(surface);
}

Spritesheet::~Spritesheet()
{
    SDL_DestroyTexture(m_spritesheet_image);
}

void Spritesheet::select_sprite(int x, int y)
{
    m_clip.x = x * m_clip.w;
    m_clip.y = y * m_clip.h;
}

void Spritesheet::draw_selected_sprite(SDL_Renderer* renderer, SDL_Rect* position)
{
    SDL_RenderCopy(renderer, m_spritesheet_image, &m_clip, position);
}
