
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <random>
#include <ctime>
#include <windows.h>
#include "gameInit.h"


void ConfigPrepare(Config & conf)
{	
	conf.backeImg.loadFromFile(conf.imageBacke);
	
};

bool isSpritesIntersected(sf::Sprite & sprite1, sf::Sprite & sprite2) {
	float widthIndentS1 = abs(sprite1.getTextureRect().width) * 0.1;
	float widthIndentS2 = abs(sprite2.getTextureRect().width) * 0.1;
	float heightIndentS1 = abs(sprite1.getTextureRect().height) * 0.2;
	float heightIndentS2 = abs(sprite2.getTextureRect().height) * 0.2;
	if (((sprite1.getPosition().x + widthIndentS1 < sprite2.getPosition().x + abs(sprite2.getTextureRect().width) - widthIndentS2) && (sprite1.getPosition().x + abs(sprite1.getTextureRect().width) - widthIndentS1 > sprite2.getPosition().x) + widthIndentS2)
		&& ((sprite1.getPosition().y + heightIndentS1 < sprite2.getPosition().y + sprite2.getTextureRect().height - heightIndentS2) && (sprite1.getPosition().y + sprite1.getTextureRect().height - heightIndentS1 > sprite2.getPosition().y + heightIndentS2))) {
		return true;
	}
	return false;
}
void createShot(GameData & gData ) {

	gData.gameSprites["bullet"].spriteItems.push_front(MySpriteDinamics(gData.gameSprites["bullet"].texture, gData.gameSprites["bullet"].frameSize, gData.gameSprites["bullet"].maxLive));
	auto bulletItr = gData.gameSprites["bullet"].spriteItems.begin();
	auto heroItr = gData.gameSprites["hero"].spriteItems.begin();
	bulletItr->mSprite.signMoveHorizont = 1;
	bulletItr->mSprite.signMoveVertical = 0;
	bulletItr->mSprite.speedKoof = 3;
	bulletItr->sprite.setPosition(heroItr->sprite.getPosition().x + abs(heroItr->sprite.getTextureRect().width), heroItr->sprite.getPosition().y + abs(heroItr->sprite.getTextureRect().height / 2));
}


void createExplotion(GameData & gData, const MySpriteDinamics & object) {
	gData.gameSprites["expl"].spriteItems.push_front(MySpriteDinamics(gData.gameSprites["expl"].texture, gData.gameSprites["expl"].frameSize, gData.gameSprites["expl"].maxLive));
	auto explItr = gData.gameSprites["expl"].spriteItems.begin();
	explItr->mSprite.signMoveHorizont = 0;
	explItr->mSprite.signMoveVertical = 0;
	explItr->mSprite.speedKoof = 1;
	int posX = object.sprite.getPosition().x + abs(object.sprite.getTextureRect().width) / 2 - gData.gameSprites["expl"].frameSize.width / 2;
	int posY = object.sprite.getPosition().y + abs(object.sprite.getTextureRect().height) / 2 - gData.gameSprites["expl"].frameSize.height / 2;
	explItr->sprite.setPosition(posX, posY);
}

/*

Возвращает
 true	враг погиб
 false	враг жив
*/
bool collisionObject(GameData & gData, MySpriteDinamics & dinamicObject, const std::string & objectKey) {
	if (objectKey == "hero") {
		for (auto enemy1Itr = gData.gameSprites["enemy1"].spriteItems.begin(); enemy1Itr != gData.gameSprites["enemy1"].spriteItems.end(); enemy1Itr++) {
			if (isSpritesIntersected(enemy1Itr->sprite, dinamicObject.sprite)) {
				gData.gameSprites["hero"].spriteItems.begin()->spriteHeal = gData.gameSprites["hero"].spriteItems.begin()->spriteHeal - gData.gameSprites["enemy1"].spriteItems.begin()->spriteHeal;
				createExplotion(gData, *enemy1Itr);
				enemy1Itr = gData.gameSprites["enemy1"].spriteItems.erase(enemy1Itr);
				return false;
			}
		}
		for (auto enemy1Itr = gData.gameSprites["enemy2"].spriteItems.begin(); enemy1Itr != gData.gameSprites["enemy2"].spriteItems.end(); enemy1Itr++) {
			if (isSpritesIntersected(enemy1Itr->sprite, dinamicObject.sprite)) {
				gData.gameSprites["hero"].spriteItems.begin()->spriteHeal = gData.gameSprites["hero"].spriteItems.begin()->spriteHeal - gData.gameSprites["enemy2"].spriteItems.begin()->spriteHeal;
				createExplotion(gData, *enemy1Itr);
				enemy1Itr = gData.gameSprites["enemy2"].spriteItems.erase(enemy1Itr);
				return false;
			}
		}
	}
	else if (objectKey == "bullet") {
		for (auto enemy1Itr = gData.gameSprites["enemy1"].spriteItems.begin(); enemy1Itr != gData.gameSprites["enemy1"].spriteItems.end(); enemy1Itr++) {
			if (isSpritesIntersected(enemy1Itr->sprite, dinamicObject.sprite)) {
				enemy1Itr->spriteHeal = enemy1Itr->spriteHeal - gData.gameSprites["bullet"].maxLive;
				if (enemy1Itr->spriteHeal <= 0) {
					createExplotion(gData, *enemy1Itr);
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
				if (enemy1Itr->spriteHeal <= 0) {
					createExplotion(gData, *enemy1Itr);
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


void GameRun(Config & conf, GameData & gData)
{
	sf::Clock clock;
	float timeCreate = conf.timeDistanceCreate;
	bool flagBG = true;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, 32700);

	while (gData.window.isOpen()) {
		if (gData.gameSprites["hero"].spriteItems.begin()->spriteHeal > 0) {
			float time = clock.getElapsedTime().asMicroseconds();
			clock.restart();
			timeCreate -= time;
			sf::Event event;


			while (gData.window.pollEvent(event)) {
				if (event.type == sf::Event::Closed ||
					(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
					gData.window.close();
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) { gData.gameSprites["hero"].spriteItems.begin()->mSprite.signMoveHorizont = -1; }
				if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Left) { gData.gameSprites["hero"].spriteItems.begin()->mSprite.signMoveHorizont = 0; }
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) { gData.gameSprites["hero"].spriteItems.begin()->mSprite.signMoveHorizont = 1; }
				if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Right) { gData.gameSprites["hero"].spriteItems.begin()->mSprite.signMoveHorizont = 0; }
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) { gData.gameSprites["hero"].spriteItems.begin()->mSprite.signMoveVertical = 1; }
				if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Down) { gData.gameSprites["hero"].spriteItems.begin()->mSprite.signMoveVertical = 0; }
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) { gData.gameSprites["hero"].spriteItems.begin()->mSprite.signMoveVertical = -1; }
				if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Up) { gData.gameSprites["hero"].spriteItems.begin()->mSprite.signMoveVertical = 0; }
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Z) { createShot(gData); }
			}
			//--------------------------бекграунд---------------------------------
			if ((gData.backeG1.getPosition().x <= 0) && (flagBG)) {
				gData.backeG2.setPosition(800, 0);
				flagBG = false;
			}
			if ((gData.backeG2.getPosition().x <= 0) && (!(flagBG))) {
				gData.backeG1.setPosition(800, 0);
				flagBG = true;
			}
			gData.backeG1.move(-2, 0);
			gData.backeG2.move(-2, 0);
			//-------------------------------------------------------------------

			for (auto staticItr = gData.gameSprites.begin(); staticItr != gData.gameSprites.end(); staticItr++) {
				if (staticItr->second.countOfItemsMAX > staticItr->second.spriteItems.size()) {
					if (timeCreate <= 0 && ((dist(gen) % 6000) < 40)) {
						staticItr->second.spriteItems.push_front(MySpriteDinamics(staticItr->second.texture, staticItr->second.frameSize, staticItr->second.maxLive));
						staticItr->second.spriteItems.begin()->mSprite.speedKoof = (dist(gen) % 12) / 10 + 0.8;
						staticItr->second.spriteItems.begin()->mSprite.moveTaktik = 1;
						staticItr->second.spriteItems.begin()->mSprite.signMoveHorizont = -1;
						staticItr->second.spriteItems.begin()->mSprite.signMoveVertical = 0;
						staticItr->second.spriteItems.begin()->sprite.setPosition(gData.window.getSize().x - 1, (dist(gen) % (gData.window.getSize().y - gData.gameSprites["enemy1"].frameSize.width)) + 1);
						timeCreate = conf.timeDistanceCreate;
					}

				}
				for (auto dinamicItr = staticItr->second.spriteItems.begin(); dinamicItr != staticItr->second.spriteItems.end(); dinamicItr) {

					// -----------------------------реализация анимации-----------------------------
					dinamicItr->frameChangeTime += sf::microseconds(time);
					sf::Time realTPF = staticItr->second.baseTPF / dinamicItr->mSprite.speedKoof;
					if (dinamicItr->frameChangeTime >= realTPF) {
						int frameInc = dinamicItr->frameChangeTime / realTPF;
						dinamicItr->frameCurrent += frameInc;
						if (staticItr->second.isCycleFrames == false && dinamicItr->frameCurrent >= staticItr->second.frameCount) {
							dinamicItr = staticItr->second.spriteItems.erase(dinamicItr);
							continue;
						}
						dinamicItr->frameCurrent = dinamicItr->frameCurrent % staticItr->second.frameCount;
						dinamicItr->frameChangeTime -= sf::microseconds(frameInc * realTPF.asMicroseconds());
					}
					//---------------------------------------движение объекта-------------------------------------
					dinamicItr->sprite.setTextureRect(sf::IntRect(staticItr->second.frameSize.width * (dinamicItr->frameCurrent + 1), 0, -staticItr->second.frameSize.width, staticItr->second.frameSize.height));
					float nextX = dinamicItr->sprite.getPosition().x + dinamicItr->mSprite.signMoveHorizont * staticItr->second.baseSpeedPx * dinamicItr->mSprite.speedKoof * time;
					float nextY = dinamicItr->sprite.getPosition().y + dinamicItr->mSprite.signMoveVertical * staticItr->second.baseSpeedPx * dinamicItr->mSprite.speedKoof * time;

					if ((nextX >= 0 && nextX < gData.window.getSize().x - staticItr->second.frameSize.width && nextY >= 0 && nextY < gData.window.getSize().y - staticItr->second.frameSize.height) || staticItr->second.isFlyOutOfScreen) {
						dinamicItr->sprite.setPosition(nextX, nextY);
					} else {
						dinamicItr->mSprite.signMoveHorizont = 0;
						dinamicItr->mSprite.signMoveVertical = 0;
					}
					if (dinamicItr->sprite.getPosition().x < -staticItr->second.frameSize.width || dinamicItr->sprite.getPosition().x > gData.window.getSize().x) {
						dinamicItr = staticItr->second.spriteItems.erase(dinamicItr);
						continue;
					}
					//-----------------------------------Взаимодействие объектов---------------------------------
					if (collisionObject(gData, *dinamicItr, staticItr->first)) {
						dinamicItr = staticItr->second.spriteItems.erase(dinamicItr);
						continue;
					}
					dinamicItr++;
				}//конец динамик
			}//конец статик

			gData.window.clear();
			gData.window.draw(gData.backeG1);
			gData.window.draw(gData.backeG2);
			for (auto staticItr = gData.gameSprites.begin(); staticItr != gData.gameSprites.end(); staticItr++) {
				for (auto dinamicItr = staticItr->second.spriteItems.begin(); dinamicItr != staticItr->second.spriteItems.end(); dinamicItr++) {
					gData.window.draw(dinamicItr->sprite);
				}
			}
			gData.window.display();
			sf::sleep(sf::microseconds(1000000 / 60.0 - clock.getElapsedTime().asMicroseconds()));
		}
	}
};

int main()
{
	Config conf;
	GameData gData;
	ConfigPrepare(conf);
	gameInitializeSprite(conf, gData);
	GameRun(conf, gData);
	return 0;
}