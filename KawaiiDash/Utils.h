#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdlib.h>
#include <string>
#include "GameDefs.h"
#include <vector>
class Utils
{
public:
	static const char* ResolvePath(const char* partialPath);
	static SDL_Rect CreateRect(int x, int y, int width, int height);
	static SDL_Texture* LoadTexture(SDL_Renderer* renderer, const char* path);
	static int RandRange(int start, int end);
	static int RandRange(int end);
	static void GetCenterRect(SDL_Rect* rect);
	static void GetTopRightRect(SDL_Rect* rect);
	static std::string Format(const std::string& format, int dummy, ...);
};

