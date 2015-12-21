#pragma once
#include "gameData.h"


bool isSpritesIntersected(sf::Sprite & sprite1, sf::Sprite & sprite2);
/*
Возвращает
true	враг погиб
false	враг жив
*/
bool collisionObject(GameData & gData, MySpriteDinamics & dinamicObject, const std::string & objectKey);
