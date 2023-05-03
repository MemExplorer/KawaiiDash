// KawaiiDash.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "GameRenderer.h"
#undef main

int main()
{
	ShowWindow(::GetConsoleWindow(), SW_HIDE);
	SetConsoleTitle(L"Kawaii Dash Console :D");
	const int FPS = 144;
	const int frameDelay = 1000 / FPS;

	uint32_t fStart;
	int fTime;

	GameRenderer* z = new GameRenderer();
	z->InitRenderer();
	while (z->GetGameState()->m_IsRunning)
	{
		fStart = SDL_GetTicks();
		z->Event();
		z->Update();
		z->Render();

		fTime = SDL_GetTicks() - fStart;
		if (frameDelay > fTime)
			SDL_Delay(frameDelay - fTime);
	}
	z->Dispose();
	delete z;
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
