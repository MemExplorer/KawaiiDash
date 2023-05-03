#include "Utils.h"

const char* Utils::ResolvePath(const char* partialPath)
{
    auto ret = _fullpath(NULL, partialPath, _MAX_PATH);
    if (ret != NULL)
        return ret;
    else
        return 0;  
}

SDL_Rect Utils::CreateRect(int x, int y, int width, int height)
{
    SDL_Rect s;
    s.x = x;
    s.y = y;
    s.w = width;
    s.h = height;
    return s;
}

SDL_Texture* Utils::LoadTexture(SDL_Renderer* renderer, const char* path)
{
    SDL_Surface* surface = IMG_Load(path);
    SDL_Texture* textureImg = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return textureImg;
}

int Utils::RandRange(int start, int end)
{
    return start + (std::rand() % (end - start));
}

int Utils::RandRange(int end)
{
    return RandRange(0, end);
}

void Utils::GetCenterRect(SDL_Rect* rect)
{
    int xcenter = WIDTH / 2;
    int ycenter = HEIGHT / 2;
    rect->x = xcenter - (rect->w / 2);
    rect->y = ycenter - (rect->h / 2);
}

void Utils::GetTopRightRect(SDL_Rect* rect)
{
    rect->x = WIDTH - (rect->w + 15);
    rect->y = (rect->h / 2);
}

std::string Utils::Format(const std::string& format, int dummy, ...)
{
    va_list args;
    va_start(args, dummy);
    size_t len = std::vsnprintf(NULL, 0, format.c_str(), args);
    va_end(args);
    std::vector<char> vec(len + 1);
    va_start(args, dummy);
    std::vsnprintf(&vec[0], len + 1, format.c_str(), args);
    va_end(args);
    return &vec[0];
}