#include "stdafx.h"
#include "gameData.h"
#include "createObjects.h"


bool isSpritesIntersected(sf::Sprite & sprite1, sf::Sprite & sprite2) {
	float widthIndentS1 = abs(sprite1.getTextureRect().width) * 0.1;
	float widthIndentS2 = abs(sprite2.getTextureRect().width) * 0.1;
	float heightIndentS1 = abs(sprite1.getTextureRect().height) * 0.2;
	float heightIndentS2 = abs(sprite2.getTextureRect().height) * 0.2;


	if (((sprite1.getPosition().x + widthIndentS1 < sprite2.getPosition().x + abs(sprite2.getTextureRect().width) - widthIndentS2)
		&& (sprite1.getPosition().x + abs(sprite1.getTextureRect().width) - widthIndentS1 > sprite2.getPosition().x + widthIndentS2))
		&& ((sprite1.getPosition().y + heightIndentS1 < sprite2.getPosition().y + sprite2.getTextureRect().height - heightIndentS2)
			&& (sprite1.getPosition().y + sprite1.getTextureRect().height - heightIndentS1 > sprite2.getPosition().y + heightIndentS2))) {
		return true;
	}
	return false;
};


/*

Возвращает
true	враг погиб
false	враг жив
*/
bool collisionObject(GameData & gData, MySpriteDinamics & dinamicObject, const std::string & objectKey) {
	if (objectKey == "enemy2" && randomNumber(30) < 1) {
		createShotForEnemy(gData, dinamicObject.sprite);
	}
	if (objectKey == "hero") {
		for (auto enemyItr = gData.gameSprites["enemy1"].spriteItems.begin(); enemyItr != gData.gameSprites["enemy1"].spriteItems.end(); enemyItr++) {
			if (isSpritesIntersected(enemyItr->sprite, dinamicObject.sprite)) {
				gData.gameSprites["hero"].spriteItems.begin()->spriteHeal = gData.gameSprites["hero"].spriteItems.begin()->spriteHeal - gData.gameSprites["enemy1"].spriteItems.begin()->spriteHeal;
				createExplotion(gData, *enemyItr, false);
				enemyItr = gData.gameSprites["enemy1"].spriteItems.erase(enemyItr);
				return false;
			}
		}
		for (auto enemyItr = gData.gameSprites["enemy2"].spriteItems.begin(); enemyItr != gData.gameSprites["enemy2"].spriteItems.end(); enemyItr++) {
			if (isSpritesIntersected(enemyItr->sprite, dinamicObject.sprite)) {
				gData.gameSprites["hero"].spriteItems.begin()->spriteHeal = gData.gameSprites["hero"].spriteItems.begin()->spriteHeal - gData.gameSprites["enemy2"].spriteItems.begin()->spriteHeal;
				createExplotion(gData, *enemyItr, false);
				enemyItr = gData.gameSprites["enemy2"].spriteItems.erase(enemyItr);
				return false;
			}
		}
		for (auto enemyItr = gData.gameSprites["bulletEnemy"].spriteItems.begin(); enemyItr != gData.gameSprites["bulletEnemy"].spriteItems.end(); enemyItr++) {
			if (isSpritesIntersected(enemyItr->sprite, dinamicObject.sprite)) {
				gData.gameSprites["hero"].spriteItems.begin()->spriteHeal = gData.gameSprites["hero"].spriteItems.begin()->spriteHeal - gData.gameSprites["bulletEnemy"].spriteItems.begin()->spriteHeal;
				createExplotion(gData, *enemyItr, true);
				enemyItr = gData.gameSprites["bulletEnemy"].spriteItems.erase(enemyItr);
				return false;
			}
		}
	} else if (objectKey == "bullet") {
		for (auto enemy1Itr = gData.gameSprites["enemy1"].spriteItems.begin(); enemy1Itr != gData.gameSprites["enemy1"].spriteItems.end(); enemy1Itr++) {
			if (isSpritesIntersected(enemy1Itr->sprite, dinamicObject.sprite)) {
				enemy1Itr->spriteHeal = enemy1Itr->spriteHeal - gData.gameSprites["bullet"].maxLive;
				createExplotion(gData, dinamicObject, true);
				if (enemy1Itr->spriteHeal <= 0) {
					createExplotion(gData, *enemy1Itr, false);
					enemy1Itr = gData.gameSprites["enemy1"].spriteItems.erase(enemy1Itr);
					return true;
				} else {
					return true;
				}
			}
		}
		for (auto enemy1Itr = gData.gameSprites["enemy2"].spriteItems.begin(); enemy1Itr != gData.gameSprites["enemy2"].spriteItems.end(); enemy1Itr++) {
			if (isSpritesIntersected(enemy1Itr->sprite, dinamicObject.sprite)) {
				enemy1Itr->spriteHeal = enemy1Itr->spriteHeal - gData.gameSprites["bullet"].maxLive;
				createExplotion(gData, dinamicObject, true);
				if (enemy1Itr->spriteHeal <= 0) {
					createExplotion(gData, *enemy1Itr, false);
					enemy1Itr = gData.gameSprites["enemy2"].spriteItems.erase(enemy1Itr);
					return true;
				} else {
					return true;
				}
			}
		}
	}
	return false;
}
