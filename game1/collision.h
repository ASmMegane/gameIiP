#pragma once
#include "gameData.h"


bool isSpritesIntersected(sf::Sprite & sprite1, sf::Sprite & sprite2);
/*
����������
true	���� �����
false	���� ���
*/
bool collisionObject(GameData & gData, MySpriteDinamics & dinamicObject, const std::string & objectKey);
