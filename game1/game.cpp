
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
#include "moveBackG.h"
#include <functional>


void ConfigPrepare(Config & conf)
{	
	conf.backeImg.loadFromFile(conf.imageBacke);
	
};

void events(sf::Event & event, GameData & gData) {
	if (event.type == sf::Event::Closed ||
		(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
		gData.window.close();
	moveingSprite &heroMove = gData.gameSprites["hero"].spriteItems.begin()->mSprite;
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) { heroMove.signMoveHorizont = -1; }
	if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Left) { heroMove.signMoveHorizont = 0; }
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) { heroMove.signMoveHorizont = 1; }
	if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Right) { heroMove.signMoveHorizont = 0; }
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) { heroMove.signMoveVertical = 1; }
	if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Down) { heroMove.signMoveVertical = 0; }
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) { heroMove.signMoveVertical = -1; }
	if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Up) { heroMove.signMoveVertical = 0; }
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Z) { createShotForHero(gData); }
}

bool moveForDinamics(MySpriteDinamics & dinamicElement, MySpriteStatics & staticElement, GameData & gData, const std::string &staticKey, float time) {

	// -----------------------------реализация анимации-------------------------------------------
	dinamicElement.frameChangeTime += (sf::microseconds((sf::Int64)time));
	sf::Time realTPF = staticElement.baseTPF / dinamicElement.mSprite.speedKoof;
	if (dinamicElement.frameChangeTime >= realTPF) {
		int frameInc = (int)(dinamicElement.frameChangeTime / realTPF);
		dinamicElement.frameCurrent += frameInc;
		if (staticElement.isCycleFrames == false && dinamicElement.frameCurrent >= staticElement.frameCount) {
			return true;
		}
		dinamicElement.frameCurrent = dinamicElement.frameCurrent % staticElement.frameCount;
		dinamicElement.frameChangeTime -= sf::microseconds(frameInc * realTPF.asMicroseconds());
	}
	//---------------------------------------движение объекта-------------------------------------
	dinamicElement.sprite.setTextureRect(sf::IntRect(staticElement.frameSize.width * (dinamicElement.frameCurrent + 1), 0, -staticElement.frameSize.width, staticElement.frameSize.height));
	float nextX = dinamicElement.sprite.getPosition().x + dinamicElement.mSprite.signMoveHorizont * staticElement.baseSpeedPx * dinamicElement.mSprite.speedKoof * time;
	float nextY = dinamicElement.sprite.getPosition().y + dinamicElement.mSprite.signMoveVertical * staticElement.baseSpeedPx * dinamicElement.mSprite.speedKoof * time;

	if ((nextX >= 0 && nextX < gData.window.getSize().x - staticElement.frameSize.width && nextY >= 0 && nextY < gData.window.getSize().y - staticElement.frameSize.height) || staticElement.isFlyOutOfScreen) {
		dinamicElement.sprite.setPosition(nextX, nextY);
	} else {
		dinamicElement.mSprite.signMoveHorizont = 0;
		dinamicElement.mSprite.signMoveVertical = 0;
	}
	if (dinamicElement.sprite.getPosition().x < -staticElement.frameSize.width || dinamicElement.sprite.getPosition().x > gData.window.getSize().x) {
		return true;
	}
	//-----------------------------------Взаимодействие объектов---------------------------------
	if (collisionObject(gData, dinamicElement, staticKey)) {
		return true;
	}
	//--------------------------------------------------------------------------------------------
	return false;
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
			while (gData.window.pollEvent(event))
				events(event, gData);
			moveBackG(gData, flagBG);

			for (auto &staticItr : gData.gameSprites) {
				createEnemy(gData, conf, timeCreate, staticItr.first);
				auto remover = std::bind(moveForDinamics,std::placeholders::_1, std::ref(staticItr.second), std::ref(gData), std::ref(staticItr.first), time);
				auto newEnd = std::remove_if(staticItr.second.spriteItems.begin(), staticItr.second.spriteItems.end(), remover);
				staticItr.second.spriteItems.erase(newEnd, staticItr.second.spriteItems.end());				
			}//конец статик

			gData.window.clear();
			gData.window.draw(gData.backeG1);
			gData.window.draw(gData.backeG2);
			for (auto &staticItr : gData.gameSprites)
				for (auto &dinamicItr : staticItr.second.spriteItems)
					gData.window.draw(dinamicItr.sprite);
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