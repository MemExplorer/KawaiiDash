#include "ObstacleLogicManager.h"


ObstacleLogicManager::ObstacleLogicManager()
{
	this->m_MultiplierCap = 3;
	this->Multiplier = 0;
	this->Add(GameEnums::BACKGROUND1, new ObstacleLogicComponent(3, -720, Utils::CreateRect(0, 0, WIDTH, HEIGHT), Utils::CreateRect(0, 0, 1200, 400)));
	this->Add(GameEnums::BACKGROUND2, new ObstacleLogicComponent(3, 0, Utils::CreateRect(WIDTH, 0, WIDTH, HEIGHT), Utils::CreateRect(0, 0, 1200, 400)));
	this->Add(GameEnums::GAME_TITLE, new ObstacleLogicComponent(0, -1, Utils::CreateRect(0, 0, 455, 100), 25, 75));
	this->Add(GameEnums::TRASHBIN, new ObstacleLogicComponent(3, -25, Utils::CreateRect(730, GROUNDPOS + 25, 25, 35), Utils::CreateRect(0, 0, 88, 132)));
	this->Add(GameEnums::DOGGO, new ObstacleLogicComponent(4, -50, Utils::CreateRect(760, GROUNDPOS + 13, 50, 50), 12, 75));
	this->Add(GameEnums::BIRDIE, new ObstacleLogicComponent(4, -40,Utils::CreateRect(750, GROUNDPOS - 30, 45, 31), 6, 75));
}

ObstacleLogicManager::~ObstacleLogicManager()
{
	for (auto i : this->m_ObstacleLogicCompMap)
		delete i.second;

	this->m_ObstacleLogicCompMap.clear();
}

void ObstacleLogicManager::Add(GameEnums::ObjectType objType, ObstacleLogicComponent* obstacleLogic)
{
	if (!this->In(objType))
		this->m_ObstacleLogicCompMap.insert({objType, obstacleLogic});
}

ObstacleLogicComponent* ObstacleLogicManager::Get(GameEnums::ObjectType objType)
{
	return this->m_ObstacleLogicCompMap.at(objType);
}

bool ObstacleLogicManager::In(GameEnums::ObjectType objType)
{
	return this->m_ObstacleLogicCompMap.find(objType) != this->m_ObstacleLogicCompMap.end();
}

void ObstacleLogicManager::IncrementVelocity()
{
	if (this->Multiplier >= 4)
		return;

	for (auto item : this->m_ObstacleLogicCompMap)
	{
		item.second->m_Velocity++;
	}
	this->Multiplier++;
}

void ObstacleLogicManager::ResetVelocity()
{
	this->Multiplier = 0;
	for (auto item : this->m_ObstacleLogicCompMap)
	{
		item.second->ResetVelocity();
	}

}