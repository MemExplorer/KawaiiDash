#include "AudioManager.h"

AudioManager::AudioManager()
{
	std::string resolved = Utils::ResolvePath("Assets/Sounds/");

	std::string playerJump1 = resolved + "jump1.wav";
	std::string playerJump2 = resolved + "jump2.wav";
	std::string playerJump3 = resolved + "jump3.wav";
	std::string playerJump4 = resolved + "jump4.wav";
	std::string playerJump5 = resolved + "jump5.wav";

	std::string playerHurt1 = resolved + "hurt1.wav";
	std::string playerHurt2 = resolved + "hurt2.wav";
	std::string playerHurt3 = resolved + "hurt3.wav";

	std::string playerDeath = resolved + "death.wav";
	
	std::string clickSound = resolved + "click.wav";
	std::string resumeSound = resolved + "resume.wav";
	std::string pauseSound = resolved + "pause.wav";
	std::string speedUpSound = resolved + "speedup.wav";

	std::string doggoHurtSound1 = resolved + "doggo1.wav";
	std::string doggoHurtSound2 = resolved + "doggo2.wav";
	std::string doggoHurtSound3 = resolved + "doggo3.wav";

	std::string birdieHurt1 = resolved + "birdie.wav";

	std::string trashBinHit = resolved + "trashbin.wav";

	GameSound* PlayerJumpGSound = new GameSound();
	PlayerJumpGSound->AddSound(playerJump1.c_str());
	PlayerJumpGSound->AddSound(playerJump2.c_str());
	PlayerJumpGSound->AddSound(playerJump3.c_str());
	PlayerJumpGSound->AddSound(playerJump4.c_str());
	PlayerJumpGSound->AddSound(playerJump5.c_str());

	GameSound* PlayerHurtGSound = new GameSound();
	PlayerHurtGSound->AddSound(playerHurt1.c_str());
	PlayerHurtGSound->AddSound(playerHurt2.c_str());
	PlayerHurtGSound->AddSound(playerHurt3.c_str());

	GameSound* PlayerDeathGSound = new GameSound();
	PlayerDeathGSound->AddSound(playerDeath.c_str());

	GameSound* GameClickSound = new GameSound();
	GameClickSound->AddSound(clickSound.c_str());

	GameSound* GameResumeSound = new GameSound();
	GameResumeSound->AddSound(resumeSound.c_str());

	GameSound* GamePauseSound = new GameSound();
	GamePauseSound->AddSound(pauseSound.c_str());

	GameSound* GameSpeedUpSound = new GameSound();
	GameSpeedUpSound->AddSound(speedUpSound.c_str());

	GameSound* DoggoHurtGSound = new GameSound();
	DoggoHurtGSound->AddSound(doggoHurtSound1.c_str());
	DoggoHurtGSound->AddSound(doggoHurtSound2.c_str());
	DoggoHurtGSound->AddSound(doggoHurtSound3.c_str());

	GameSound* BirdieHurtSound = new GameSound();
	BirdieHurtSound->AddSound(birdieHurt1.c_str());

	GameSound* TrashBinHitSound = new GameSound();
	TrashBinHitSound->AddSound(trashBinHit.c_str());


	this->Add(GameSoundType::PLAYER_JUMP, PlayerJumpGSound);
	this->Add(GameSoundType::PLAYER_HURT, PlayerHurtGSound);
	this->Add(GameSoundType::PLAYER_DEAD, PlayerDeathGSound);

	this->Add(GameSoundType::PLAYER_TAP, GameClickSound);
	this->Add(GameSoundType::GAME_RESUME, GameResumeSound);
	this->Add(GameSoundType::GAME_PAUSE, GamePauseSound);
	this->Add(GameSoundType::DIFFICULTY_INCREASE, GameSpeedUpSound);
	
	this->Add(GameSoundType::DOGGO_HURT, DoggoHurtGSound);
	this->Add(GameSoundType::BIRDIE_HURT, BirdieHurtSound);
	this->Add(GameSoundType::TRASH_HIT, TrashBinHitSound);
}

AudioManager::~AudioManager()
{
	for (auto i : this->m_gameSoundMap)
		delete i.second;

	this->m_gameSoundMap.clear();
}

void AudioManager::Add(GameSoundType::GameSoundType soundType, GameSound* gameSound)
{
	if (!this->In(soundType))
		this->m_gameSoundMap.insert({soundType, gameSound });
}

bool AudioManager::In(GameSoundType::GameSoundType soundType)
{
	return this->m_gameSoundMap.find(soundType) != this->m_gameSoundMap.end();
}

void AudioManager::GPlaySound(GameSoundType::GameSoundType soundType)
{
	this->GPlaySound(soundType, false);
}

void AudioManager::GPlaySound(GameSoundType::GameSoundType soundType, bool hasCD)
{
	this->m_gameSoundMap.at(soundType)->GPlaySound(hasCD);
}
