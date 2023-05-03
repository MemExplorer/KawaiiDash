#include "GameRenderer.h"

void GameRenderer::SetWindowTitle(const char* title)
{
	SDL_SetWindowTitle(m_CurrentWindow, title);
}

//threadings

void TripPlayerThread(GameRenderer* gRenderer)
{
	gRenderer->m_CurrentPlayer->m_IsJumping = false;
	gRenderer->m_CurrentPlayer->m_tripFrameStart++;
	Sleep(80);
	gRenderer->m_CurrentPlayer->m_tripFrameStart++;
	Sleep(50);
	gRenderer->m_CurrentPlayer->m_tripFrameStart++;
	Sleep(20);
	gRenderer->m_GameInstance->m_PlayerDeadCD = false;
	gRenderer->m_GameInstance->m_StartCD = false;

	//wait for player to be on land before we can pause
	while (!gRenderer->m_CurrentPlayer->m_OnLand || gRenderer->m_GameInstance->m_StartCD);
	Sleep(50);
	gRenderer->m_GameInstance->m_PauseRenderer = true;
}

void SpawnObstaclesThread(GameRenderer* gRenderer)
{
	while (gRenderer->m_GameInstance->m_IsRunning)
	{
		//prevent them from spawning too often after resuming
		if (gRenderer->m_GameInstance->m_Paused || gRenderer->m_GameInstance->m_StartCD)
			continue;

		if (gRenderer->m_GameInstance->m_GameStarted)
		{
			if (gRenderer->m_ObstacleVec.size() < 3)
			{
				gRenderer->SpawnObstacles();
				
				//halt sleep timer
				while ((gRenderer->m_GameInstance->m_Paused || gRenderer->m_GameInstance->m_StartCD));
				Sleep(900 + (gRenderer->m_ObstacleLogicManager->Multiplier * 250));
			}

		}

		Sleep(10);
	}
}

void PauseStartDelay(GameRenderer* gRenderer)
{
	GameTextObject* textObj = gRenderer->m_GameTextManager->Get(GameTextType::START_SCREEN_MESSAGE);
	textObj->m_Visible = true;
	textObj->UpdateText("3");
	Utils::GetCenterRect(&textObj->m_ObjectRect);
	Sleep(1000);
	textObj->UpdateText("2");
	Utils::GetCenterRect(&textObj->m_ObjectRect);
	Sleep(1000);
	textObj->UpdateText("1");
	Utils::GetCenterRect(&textObj->m_ObjectRect);
	Sleep(1000);
	gRenderer->m_GameInstance->m_Paused = !gRenderer->m_GameInstance->m_Paused;
	textObj->UpdateText("Go");
	Utils::GetCenterRect(&textObj->m_ObjectRect);
	Sleep(1000);
	textObj->m_Visible = false;
	gRenderer->m_GameInstance->m_StartCD = false;
}

void GameStartDelayThread(GameRenderer* gRenderer)
{
	GameTextObject* textObj = gRenderer->m_GameTextManager->Get(GameTextType::START_SCREEN_MESSAGE);
	textObj->m_Visible = true;
	textObj->UpdateText("3");
	Utils::GetCenterRect(&textObj->m_ObjectRect);
	Sleep(1000);
	textObj->UpdateText("2");
	Utils::GetCenterRect(&textObj->m_ObjectRect);
	Sleep(1000);
	textObj->UpdateText("1");
	Utils::GetCenterRect(&textObj->m_ObjectRect);
	Sleep(1000);
	gRenderer->m_GameInstance->m_GameStarted = true;
	textObj->UpdateText("Go");
	Utils::GetCenterRect(&textObj->m_ObjectRect);
	Sleep(1000);
	textObj->m_Visible = false;
	gRenderer->m_GameInstance->m_StartCD = false;
}

void InvincibilityThread(GameRenderer* gRenderer)
{
	//invincibility state on
	for (int i = 0; i < 6; i++)
	{
		gRenderer->m_CurrentPlayer->m_Visible = !gRenderer->m_CurrentPlayer->m_Visible;
		Sleep(200 - (i * 5));
	}

	for (int i = 0; i < 10; i++)
	{
		gRenderer->m_CurrentPlayer->m_Visible = !gRenderer->m_CurrentPlayer->m_Visible;
		Sleep(100 - (i * 5));
	}

	//invincibility state off
	gRenderer->m_GameInstance->m_Invincibility = false;
}

void ScoreCDThread(GameRenderer* gRenderer)
{
	Sleep(3000);
	gRenderer->m_GameInstance->m_ScoreCD = false;
}

void GameRenderer::InitRenderer()
{
	//Initialize SDL stuff
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	TTF_Init();
	int audio_rate = 22050; 
	Uint16 audio_format = AUDIO_S16SYS; 
	int audio_channels = 2; 
	int audio_buffers = 4096;

	if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) 
	{ 
		fprintf(stderr, "Unable to initialize audio: %s\n", Mix_GetError()); 
		exit(1); 
	}

	SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_SHOWN, &m_CurrentWindow, &m_Renderer);

	if (!m_CurrentWindow)
		throw std::exception("Error initializing window!");

	SetWindowTitle("Kawaii Dash :D");

	//initialize game managers
	this->m_GameTextManager = new GameTextManager();
	this->m_TextureManager = new TextureManager(this->m_Renderer);
	this->m_SpriteManager = new SpriteManager(this->m_Renderer);
	this->m_AudioManager = new AudioManager();
	this->m_ObstacleLogicManager = new ObstacleLogicManager();
	this->m_ObstacleManager = new ObstacleManager(this->m_ObstacleLogicManager, this->m_SpriteManager, this->m_TextureManager);

	//initialize player
	m_CurrentPlayer = new Player(this->m_SpriteManager->Get(GameEnums::PLAYER), 20, GROUNDPOS, CHARACTER_SIZE);

	//initialize game state
	this->m_GameInstance = new GameState();

	//start obstacle spawning thread
	this->t_spawnObstacles = std::thread(SpawnObstaclesThread, this);
	this->t_spawnObstacles.detach();

	//play game music
	const char* BGMusicPath = Utils::ResolvePath("Assets/Sounds/Slime Time.mp3");
	this->BGM = Mix_LoadMUS(BGMusicPath);
	Mix_MasterVolume(20);
	Mix_VolumeMusic(15);
	Mix_PlayMusic(this->BGM, -1);
}

bool GameRenderer::CheckCollision(GameObject* Obja, GameObject* Objb)
{
	SDL_Rect a = Obja->m_ObjectRect;
	SDL_Rect b = Objb->m_ObjectRect;

	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	//If any of the sides from A are outside of B
	return !(leftA >= rightB - 20 || rightA <= leftB + 20 || topA >= bottomB - 20 || bottomA <= topB + 20);
}

GameState* GameRenderer::GetGameState()
{
	return this->m_GameInstance;
}

void GameRenderer::Dispose()
{

	//dispose managers and game object
	delete this->m_GameInstance;
	delete this->m_CurrentPlayer;
	delete this->m_ObstacleManager;
	delete this->m_ObstacleLogicManager;
	delete this->m_SpriteManager;
	delete this->m_TextureManager;
	delete this->m_GameTextManager;
	delete this->m_AudioManager;


	//dispose obstacles
	for (Obstacle* obstacle : this->m_ObstacleVec)
		delete obstacle;

	this->m_ObstacleVec.clear();
	Mix_FreeMusic(this->BGM);

	//free sdl stuff
	TTF_Quit();
	Mix_CloseAudio();
	Mix_Quit();
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_CurrentWindow);
	SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
	SDL_Quit();
}


void GameRenderer::Event()
{
	SDL_PollEvent(&m_Evt);
	switch (m_Evt.type)
	{
		case SDL_KEYDOWN:
		{
			auto currentKey = m_Evt.key.keysym.sym;
			switch (currentKey)
			{
			case SDLK_x:
			{
				exit(0);
				break;
			}
			case SDLK_p:
			{
				//pause game
				if (this->m_GameInstance->m_GameStarted)
				{
					GameTextObject* pauseMessage = this->m_GameTextManager->Get(GameTextType::PAUSE_TEXT_MESSAGE);
					if (!this->m_GameInstance->m_StartCD && this->m_GameInstance->m_Paused)
					{
						this->m_AudioManager->GPlaySound(GameSoundType::GAME_RESUME, true);
						pauseMessage->m_Visible = false;
						this->m_GameInstance->m_StartCD = true;
						this->t_pauseDelay = std::thread(PauseStartDelay, this);
						this->t_pauseDelay.detach();
					}
					else if(!this->m_GameInstance->m_StartCD)
					{
						pauseMessage->m_Visible = true;
						this->m_GameInstance->m_Paused = !this->m_GameInstance->m_Paused;
						this->m_AudioManager->GPlaySound(GameSoundType::GAME_PAUSE, true);
					}
				}
			}
			break;
			case SDLK_w:
			case SDLK_SPACE:
			{
				//jump control
				if (this->m_GameInstance->m_Paused || this->m_GameInstance->IsPlayerDead())
					break;
				m_CurrentPlayer->Jump();
				this->m_AudioManager->GPlaySound(GameSoundType::PLAYER_JUMP, true);
			}
			break;
			}
		}
		break;

		case SDL_MOUSEBUTTONDOWN:
		{
			if (this->m_GameInstance->m_PauseRenderer)
			{
				this->m_AudioManager->GPlaySound(GameSoundType::PLAYER_TAP);
				//reset game state
				this->m_GameInstance->GameReset();

				//reset game message
				Obstacle* titleObj = m_ObstacleManager->Get(GameEnums::GAME_TITLE);
				GameTextObject* controlsMessage = this->m_GameTextManager->Get(GameTextType::CONTROLS_TEXT_MESSAGE);
				GameTextObject* startMessage = this->m_GameTextManager->Get(GameTextType::START_SCREEN_MESSAGE);
				startMessage->m_Visible = true;
				titleObj->m_Visible = true;
				controlsMessage->m_Visible = true;
				startMessage->UpdateText("Click anywhere to start...");
				Utils::GetCenterRect(&startMessage->m_ObjectRect);
				startMessage->m_ObjectRect.y += 30;

				//clear obstacles
				this->m_ObstacleVec.clear();

				//reset character state
				this->m_CurrentPlayer->ResetState();

				//reset multiplier
				this->m_ObstacleLogicManager->ResetVelocity();
			}
			else if (!this->m_GameInstance->m_StartCD && !this->m_GameInstance->m_GameStarted && m_Evt.button.button == SDL_BUTTON_LEFT)
			{
				Obstacle* titleObj = m_ObstacleManager->Get(GameEnums::GAME_TITLE);
				GameTextObject* controlsMessage = this->m_GameTextManager->Get(GameTextType::CONTROLS_TEXT_MESSAGE);
				this->m_AudioManager->GPlaySound(GameSoundType::PLAYER_TAP);
				this->m_GameInstance->m_StartCD = true;
				titleObj->m_Visible = false;
				controlsMessage->m_Visible = false;
				this->t_gameStartThread = std::thread(GameStartDelayThread, this);
				this->t_gameStartThread.detach();
			}
		}
		break;

		case SDL_QUIT:
		{
			this->m_GameInstance->m_IsRunning = false;
			break;
		}

		case SDL_KEYUP:
			break;
	}
}

void GameRenderer::SpawnObstacles()
{
	//obstacle spawning
	int obstacleType = Utils::RandRange(100);
	if (obstacleType % 12 == 0)
	{
		Obstacle* Doggo = this->m_ObstacleManager->Get(GameEnums::DOGGO);
		this->m_ObstacleVec.push_back(new Obstacle(*Doggo));
	}
	else if (obstacleType % 11 == 0)
	{
		Obstacle* Birdie = this->m_ObstacleManager->Get(GameEnums::BIRDIE);
		int pos = Utils::RandRange(10);
		Birdie->m_ObjectRect.y = Birdie->m_LogicComponent->m_ObstaclePos.y - 20;
		if (pos % 2 == 0)
			Birdie->m_ObjectRect.y = Birdie->m_LogicComponent->m_ObstaclePos.y + 60;

		this->m_ObstacleVec.push_back(new Obstacle(*Birdie));
	}
	else
	{
		Obstacle* TrashBin = this->m_ObstacleManager->Get(GameEnums::TRASHBIN);
		this->m_ObstacleVec.push_back(new Obstacle(*TrashBin));
	}
}

void GameRenderer::Update()
{
	m_CurrentPlayer->Update(this->m_GameInstance);
	if (this->m_GameInstance->IsPlayerDead())
		return;

	//background looping update and checks
	Obstacle* BG1 = m_ObstacleManager->Get(GameEnums::BACKGROUND1);
	Obstacle* BG2 = m_ObstacleManager->Get(GameEnums::BACKGROUND2);
	BG1->Update(this->m_GameInstance);
	BG2->Update(this->m_GameInstance);

	if (BG1->m_ObjectRect.x <= BG1->m_LogicComponent->m_DespawnOffset)
		BG1->m_ObjectRect.x = BG1->m_LogicComponent->m_ObstaclePos.x;

	if (BG2->m_ObjectRect.x <= BG2->m_LogicComponent->m_DespawnOffset)
		BG2->m_ObjectRect.x = BG2->m_LogicComponent->m_ObstaclePos.x;

	//obstacle updates
	if (this->m_GameInstance->m_GameStarted)
	{
		for (int i = 0; i < this->m_ObstacleVec.size(); i++)
		{
			Obstacle* o = this->m_ObstacleVec.at(i);
			o->Update(this->m_GameInstance);

			//check if player hits an obstacle
			if (CheckCollision(this->m_CurrentPlayer, o))
			{
				if (this->m_GameInstance->m_Invincibility)
					continue;

				this->m_GameInstance->m_Lives--;
				
				if (o->m_ObjectType == GameEnums::TRASHBIN)
					this->m_AudioManager->GPlaySound(GameSoundType::TRASH_HIT);
				else if(o->m_ObjectType == GameEnums::BIRDIE)
					this->m_AudioManager->GPlaySound(GameSoundType::BIRDIE_HURT);
				else if (o->m_ObjectType == GameEnums::DOGGO)
					this->m_AudioManager->GPlaySound(GameSoundType::DOGGO_HURT);

				if (this->m_GameInstance->m_Lives <= 0)
				{
					//player dead
					int currScore = this->m_GameInstance->GetScore();
					if (currScore > this->m_GameInstance->m_HighScore)
					{
						this->m_GameInstance->m_HighScore = currScore;
						GameTextObject* hiScoreTxtObj = m_GameTextManager->Get(GameTextType::HI_SCORE_TEXT_MESSAGE);
						hiScoreTxtObj->UpdateText(Utils::Format("hi %06d", 0, this->m_GameInstance->m_HighScore));
					}

					GameTextObject* screenMessage = this->m_GameTextManager->Get(GameTextType::START_SCREEN_MESSAGE);
					screenMessage->m_Visible = false;
					this->m_GameInstance->m_StartCD = true;
					this->m_GameInstance->m_PlayerDeadCD = true;
					this->t_tripPlayer = std::thread(TripPlayerThread, this);
					this->t_tripPlayer.detach();
					this->m_AudioManager->GPlaySound(GameSoundType::PLAYER_DEAD);
					
					return;
				}
				else
				{
					//decrement lives
					if (!this->m_GameInstance->m_Invincibility)
					{
						this->m_AudioManager->GPlaySound(GameSoundType::PLAYER_HURT);
						this->m_GameInstance->m_Invincibility = true;
						this->t_invincibilityThread = std::thread(InvincibilityThread, this);
						this->t_invincibilityThread.detach();
					}
				}
			}

			//remove obstacle since it is no longer on the screen
			if (o->m_ObjectRect.x <= o->m_LogicComponent->m_DespawnOffset)
			{
				delete o;
				this->m_ObstacleVec.erase(this->m_ObstacleVec.begin() + i);
				i--;
			}
		}

	}


	//update score
	this->m_GameInstance->IncrementScore();

	if (!this->m_GameInstance->m_ScoreCD && 
		this->m_GameInstance->GetScore() >= 1000 &&
		this->m_GameInstance->GetScore() % 1000 == 0)
	{
		this->m_AudioManager->GPlaySound(GameSoundType::DIFFICULTY_INCREASE);
		this->m_GameInstance->m_ScoreCD = true;
		this->m_ObstacleLogicManager->IncrementVelocity();	
		this->t_scoreCD = std::thread(ScoreCDThread, this);
		this->t_scoreCD.detach();
	}

	GameTextObject* scoreTxtObj = m_GameTextManager->Get(GameTextType::SCORE_TEXT_MESSAGE);
	GameTextObject* hiScoreTxtObj = m_GameTextManager->Get(GameTextType::HI_SCORE_TEXT_MESSAGE);
	std::string scoreUpdateText = Utils::Format("Score %06d", 0, this->m_GameInstance->GetScore());
	scoreTxtObj->UpdateText(scoreUpdateText, false);
	Utils::GetTopRightRect(&scoreTxtObj->m_ObjectRect);
	Utils::GetTopRightRect(&hiScoreTxtObj->m_ObjectRect);
	scoreTxtObj->m_ObjectRect.x -= 10;
	hiScoreTxtObj->m_ObjectRect.x -= (20 + scoreTxtObj->m_ObjectRect.w);
}

void GameRenderer::Render()
{
	if (this->m_GameInstance->m_PauseRenderer)
		return;

	SDL_RenderClear(m_Renderer);

	//render background
	m_ObstacleManager->Get(GameEnums::BACKGROUND1)->Render(m_Renderer);
	m_ObstacleManager->Get(GameEnums::BACKGROUND2)->Render(m_Renderer);

	
	if (this->m_GameInstance->m_GameStarted)
	{

		//render hearts and obstacles
		for (Obstacle* o : this->m_ObstacleVec)
			o->Render(m_Renderer);

		SDL_Texture* heartTex = this->m_TextureManager->Get(GameEnums::HEART);
		SDL_Texture* shatteredHeartTex = this->m_TextureManager->Get(GameEnums::SHATTERED_HEART);
		SDL_Rect heartSrcRect = Utils::CreateRect(0, 0, 85, 75);
		for (int i = 0; i < this->m_GameInstance->m_MaxLives; i++)
		{
			int heartWidth = 27;
			int heartHeight = 24;
			SDL_Rect dstRect = Utils::CreateRect(10 + (i * heartWidth), heartHeight / 2, heartWidth, heartHeight);
			if(i + 1 <= this->m_GameInstance->m_Lives)
				SDL_RenderCopy(m_Renderer, heartTex, &heartSrcRect, &dstRect);
			else
				SDL_RenderCopy(m_Renderer, shatteredHeartTex, &heartSrcRect, &dstRect);
		}
	}

	//render game message
	GameTextObject* screenMessage = this->m_GameTextManager->Get(GameTextType::START_SCREEN_MESSAGE);
	GameTextObject* scoreMessage = this->m_GameTextManager->Get(GameTextType::SCORE_TEXT_MESSAGE);
	GameTextObject* hiScoreMessage = this->m_GameTextManager->Get(GameTextType::HI_SCORE_TEXT_MESSAGE);
	GameTextObject* pauseMessage = this->m_GameTextManager->Get(GameTextType::PAUSE_TEXT_MESSAGE);
	GameTextObject* deathMessage = this->m_GameTextManager->Get(GameTextType::DEATH_TEXT_MESSAGE);
	screenMessage->Render(m_Renderer);

	if (screenMessage->m_Visible)
	{
		Obstacle* titleObj = m_ObstacleManager->Get(GameEnums::GAME_TITLE);
		GameTextObject* controlsMessage = this->m_GameTextManager->Get(GameTextType::CONTROLS_TEXT_MESSAGE);

		Utils::GetCenterRect(&titleObj->m_ObjectRect);
		titleObj->m_ObjectRect.y -= 80;
		titleObj->Render(m_Renderer);

		Utils::GetCenterRect(&controlsMessage->m_ObjectRect);
		controlsMessage->m_ObjectRect.y += 160;
		controlsMessage->Render(m_Renderer);
	}
	
	if (this->m_GameInstance->IsPlayerDead())
		deathMessage->Render(m_Renderer);

	if (this->m_GameInstance->m_Paused)
		pauseMessage->Render(m_Renderer);

	if (this->m_GameInstance->m_GameStarted)
	{
		scoreMessage->Render(m_Renderer);
		hiScoreMessage->Render(m_Renderer);
	}

	//render player
	if (this->m_GameInstance->IsPlayerDead())
		m_CurrentPlayer->RenderTripped(m_Renderer);
	else
		m_CurrentPlayer->Render(m_Renderer);

	SDL_RenderPresent(m_Renderer);
}