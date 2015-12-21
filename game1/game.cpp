
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <random>
#include <ctime>
#include <windows.h>
#include "gameInit.h"
#include "collision.h"
#include "createObjects.h"


void ConfigPrepare(Config & conf)
{	
	conf.backeImg.loadFromFile(conf.imageBacke);
	
};

void events(sf::Event & event, GameData & gData) {
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
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Z) { createShotForHero(gData); }
}


void GameRun(Config & conf, GameData & gData)
{
	sf::Clock clock;
	float timeCreate = conf.timeDistanceCreate;
	bool flagBG = true;

	while (gData.window.isOpen()) {
		if (gData.gameSprites["hero"].spriteItems.begin()->spriteHeal > 0) {
			float time = (float)clock.getElapsedTime().asMicroseconds();
			clock.restart();
			timeCreate -= time;
			sf::Event event;
			//------------------------события-------------------------------------
			while (gData.window.pollEvent(event))
				events(event, gData);
			//--------------------------------------------------------------------
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
			//----------------------------------------------------------------------------------------------------

			for (auto staticItr = gData.gameSprites.begin(); staticItr != gData.gameSprites.end(); staticItr++) {
				createEnemy(gData, conf, timeCreate, staticItr->first);

				for (auto dinamicItr = staticItr->second.spriteItems.begin(); dinamicItr != staticItr->second.spriteItems.end(); dinamicItr) {

					// -----------------------------реализация анимации-------------------------------------------
					dinamicItr->frameChangeTime += (sf::microseconds((sf::Int64)time));
					sf::Time realTPF = staticItr->second.baseTPF / dinamicItr->mSprite.speedKoof;
					if (dinamicItr->frameChangeTime >= realTPF) {
						int frameInc = (int)(dinamicItr->frameChangeTime / realTPF);
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
					//--------------------------------------------------------------------------------------------
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
			sf::sleep(sf::microseconds((sf::Int64)(1000000 / 60.0 - clock.getElapsedTime().asMicroseconds())));
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