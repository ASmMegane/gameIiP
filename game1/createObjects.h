#pragma once
#include "gameData.h"

int randomNumber(const int & size);
void createEnemy(GameData & gData, Config & conf, float & timeCreate, std::string const & keyStatic);
void createShotForEnemy(GameData & gData, sf::Sprite & spriteEnemy);
void createShotForHero(GameData & gData);
void createExplotion(GameData & gData, const MySpriteDinamics & object, const bool & isBullet);
