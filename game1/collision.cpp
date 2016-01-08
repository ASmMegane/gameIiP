#include "stdafx.h"
#include "gameData.h"
#include "createObjects.h"


bool isSpritesIntersected(sf::Sprite & sprite1, sf::Sprite & sprite2) {
	float indentValue = 0.2f;
	float widthIndentS1 = abs(sprite1.getTextureRect().width) * indentValue;
	float widthIndentS2 = abs(sprite2.getTextureRect().width) * indentValue;
	float heightIndentS1 = abs(sprite1.getTextureRect().height) * indentValue;
	float heightIndentS2 = abs(sprite2.getTextureRect().height) * indentValue;

	if (!(sprite1.getPosition().x + widthIndentS1 < sprite2.getPosition().x + abs(sprite2.getTextureRect().width) - widthIndentS2))
		return false;
	if (!(sprite1.getPosition().x + abs(sprite1.getTextureRect().width) - widthIndentS1 > sprite2.getPosition().x + widthIndentS2))
		return false;
	if (!(sprite1.getPosition().y + heightIndentS1 < sprite2.getPosition().y + abs(sprite2.getTextureRect().height) - heightIndentS2))
		return false;
	if (!(sprite1.getPosition().y + sprite1.getTextureRect().height - heightIndentS1 > sprite2.getPosition().y + heightIndentS2))
		return false;
	return true;
};


bool collisionObject(GameData & gData, MySpriteDinamics & dinamicObject, const std::string & objectKey) {
	if (objectKey == "enemy2" && randomNumber(30) < 1) {
		createShotForEnemy(gData, dinamicObject.sprite);
	}
	std::list<MySpriteDinamics> &enemy1Sprites = gData.gameSprites["enemy1"].spriteItems;
	std::list<MySpriteDinamics> &enemy2Sprites = gData.gameSprites["enemy2"].spriteItems;
	if (objectKey == "hero") { //----------------------столкновение с героем----------------
		int heroHeal = gData.gameSprites["hero"].spriteItems.begin()->spriteHeal;
		for (auto enemyItr = enemy1Sprites.begin(); enemyItr != enemy1Sprites.end(); enemyItr++) {
			if (isSpritesIntersected(enemyItr->sprite, dinamicObject.sprite)) {
				heroHeal = heroHeal - enemy1Sprites.begin()->spriteHeal;
				createExplotion(gData, *enemyItr, false);
				enemyItr = enemy1Sprites.erase(enemyItr);
				return false;
			}
		}
		for (auto enemyItr = enemy2Sprites.begin(); enemyItr != enemy2Sprites.end(); enemyItr++) {
			if (isSpritesIntersected(enemyItr->sprite, dinamicObject.sprite)) {
				heroHeal = heroHeal - enemy2Sprites.begin()->spriteHeal;
				createExplotion(gData, *enemyItr, false);
				enemyItr = enemy2Sprites.erase(enemyItr);
				return false;
			}
		}
		std::list<MySpriteDinamics> &enemysBulletSprites = gData.gameSprites["bulletEnemy"].spriteItems;
		for (auto enemyItr = enemysBulletSprites.begin(); enemyItr != enemysBulletSprites.end(); enemyItr++) {
			if (isSpritesIntersected(enemyItr->sprite, dinamicObject.sprite)) {
				heroHeal = heroHeal - enemysBulletSprites.begin()->spriteHeal;
				createExplotion(gData, *enemyItr, true);
				enemyItr = enemysBulletSprites.erase(enemyItr);
				return false;
			}
		}
	} else if (objectKey == "bullet") { //---------------------столкновение с пулей героя-------------------
		int &bulletHeroLive = gData.gameSprites["bullet"].maxLive;
		for (auto enemy1Itr = enemy1Sprites.begin(); enemy1Itr != enemy1Sprites.end(); enemy1Itr++) {
			if (isSpritesIntersected(enemy1Itr->sprite, dinamicObject.sprite)) {
				enemy1Itr->spriteHeal = enemy1Itr->spriteHeal - bulletHeroLive;
				createExplotion(gData, dinamicObject, true);
				if (enemy1Itr->spriteHeal <= 0) {
					createExplotion(gData, *enemy1Itr, false);
					enemy1Itr = enemy1Sprites.erase(enemy1Itr);
					return true;
				} 
				return true;
			}
		}
		for (auto enemy1Itr = enemy2Sprites.begin(); enemy1Itr != enemy2Sprites.end(); enemy1Itr++) {
			if (isSpritesIntersected(enemy1Itr->sprite, dinamicObject.sprite)) {
				enemy1Itr->spriteHeal = enemy1Itr->spriteHeal - bulletHeroLive;
				createExplotion(gData, dinamicObject, true);
				if (enemy1Itr->spriteHeal <= 0) {
					createExplotion(gData, *enemy1Itr, false);
					enemy1Itr = enemy2Sprites.erase(enemy1Itr);
					return true;
				} 
				return true;
			}
		}
	}
	return false;
}
