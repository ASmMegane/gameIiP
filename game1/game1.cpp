
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
	float heightIndentS1 = abs(sprite1.getTextureRect().height) * 0.1;
	float heightIndentS2 = abs(sprite2.getTextureRect().height) * 0.1;
	if (((sprite1.getPosition().x + widthIndentS1 < sprite2.getPosition().x + abs(sprite2.getTextureRect().width) - widthIndentS2) && (sprite1.getPosition().x + abs(sprite1.getTextureRect().width) - widthIndentS1 > sprite2.getPosition().x) + widthIndentS2)
		&& ((sprite1.getPosition().y + heightIndentS1 < sprite2.getPosition().y + sprite2.getTextureRect().height - heightIndentS2) && (sprite1.getPosition().y + sprite1.getTextureRect().height - heightIndentS1 > sprite2.getPosition().y + heightIndentS2))) {
		return true;
	}
	return false;
}
void createShot(GameData & gData ) {

	gData.gameSprites["bullet"].spriteItems.push_front(MySpriteDinamics(gData.gameSprites["bullet"].texture));
	auto bulletItr = gData.gameSprites["bullet"].spriteItems.begin();
	auto heroItr = gData.gameSprites["hero"].spriteItems.begin();
	bulletItr->mSprite.signMoveHorizont = 1;
	bulletItr->mSprite.signMoveVertical = 0;
	bulletItr->mSprite.speedKoof = 3;
	bulletItr->sprite.setPosition(heroItr->sprite.getPosition().x + abs(heroItr->sprite.getTextureRect().width), heroItr->sprite.getPosition().y + abs(heroItr->sprite.getTextureRect().height / 2));
}

void GameRun(Config & conf, GameData & gData)
{
	sf::Clock clock;
	float timeCreate = conf.timeDistanceCreate;

	while (gData.window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		timeCreate -= time;
		sf::Event event;
		
		
		while (gData.window.pollEvent(event))
		{			
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


		if ((gData.backeG1.getPosition().x < 0) && (gData.backeG1.getPosition().x > -1)) {gData.backeG2.setPosition(800,0); }
		if ((gData.backeG2.getPosition().x < 0) && (gData.backeG2.getPosition().x > -1)) {gData.backeG1.setPosition(800,0); }
		gData.backeG1.move(-0.0001*time, 0);
		gData.backeG2.move(-0.0001*time, 0);

		


		for (auto staticItr = gData.gameSprites.begin(); staticItr != gData.gameSprites.end(); staticItr++) {
			if (staticItr->second.countOfItemsMAX > staticItr->second.spriteItems.size()) {
				std::random_device rd;
				std::mt19937 gen(rd());
				std::uniform_int_distribution<> dist(0, 32700);
				if (timeCreate <= 0 && ((dist(gen) % 100) < 1)) {
					staticItr->second.spriteItems.push_front(MySpriteDinamics(staticItr->second.texture));
					staticItr->second.spriteItems.begin()->mSprite.speedKoof = (dist(gen) % 22) / 10 + 0.8;
					staticItr->second.spriteItems.begin()->mSprite.moveTaktik = 1;
					staticItr->second.spriteItems.begin()->mSprite.signMoveHorizont = -1;
					staticItr->second.spriteItems.begin()->mSprite.signMoveVertical = 0;
					staticItr->second.spriteItems.begin()->sprite.setPosition(gData.window.getSize().x - 1, (dist(gen) % (gData.window.getSize().y - gData.gameSprites["enemy1"].frameSize.width)) + 1);
					timeCreate = conf.timeDistanceCreate;
				}

			}
			for (auto dinamicItr = staticItr->second.spriteItems.begin(); dinamicItr != staticItr->second.spriteItems.end(); dinamicItr) {
				
				// реализация анимации
				dinamicItr->frameChangeTime += sf::microseconds(time);
				sf::Time realTPF = staticItr->second.baseTPF / dinamicItr->mSprite.speedKoof;
				if (dinamicItr->frameChangeTime >= realTPF) {
					int frameInc = dinamicItr->frameChangeTime / realTPF;
					dinamicItr->frameCurrent += frameInc;
					dinamicItr->frameCurrent = dinamicItr->frameCurrent % staticItr->second.frameCount;
					dinamicItr->frameChangeTime -= sf::microseconds(frameInc * realTPF.asMicroseconds());
				}
				dinamicItr->sprite.setTextureRect(sf::IntRect(staticItr->second.frameSize.width * (dinamicItr->frameCurrent + 1), 0, -staticItr->second.frameSize.width, staticItr->second.frameSize.height));
				float nextX = dinamicItr->sprite.getPosition().x + dinamicItr->mSprite.signMoveHorizont*staticItr->second.baseSpeedPx * dinamicItr->mSprite.speedKoof * time;
				float nextY = dinamicItr->sprite.getPosition().y + dinamicItr->mSprite.signMoveVertical*staticItr->second.baseSpeedPx * dinamicItr->mSprite.speedKoof * time;

				if ((nextX >= 0 && nextX < gData.window.getSize().x - staticItr->second.frameSize.width && nextY >= 0 && nextY < gData.window.getSize().y - staticItr->second.frameSize.height) || staticItr->second.isFlyOutOfScreen) {
					dinamicItr->sprite.setPosition(nextX, nextY);
				} 
				else {
					dinamicItr->mSprite.signMoveHorizont = 0;
					dinamicItr->mSprite.signMoveVertical = 0;
				}			

				if (dinamicItr->sprite.getPosition().x < -staticItr->second.frameSize.width) {
					dinamicItr = staticItr->second.spriteItems.erase(dinamicItr);
				}
				else if (isSpritesIntersected(dinamicItr->sprite, gData.gameSprites["hero"].spriteItems.begin()->sprite) && staticItr->first != "hero") {
					dinamicItr = staticItr->second.spriteItems.erase(dinamicItr);
				}
				else if (staticItr->first != "hero" && staticItr->first != "bullet") {

					auto bulletItr = gData.gameSprites["bullet"].spriteItems.begin();
					while(bulletItr != gData.gameSprites["bullet"].spriteItems.end()) {
						if (isSpritesIntersected(dinamicItr->sprite, bulletItr->sprite)) {
							break;
						}
						bulletItr++;
					}
					if (bulletItr != gData.gameSprites["bullet"].spriteItems.end()) {
						dinamicItr = staticItr->second.spriteItems.erase(dinamicItr);
						gData.gameSprites["bullet"].spriteItems.erase(bulletItr);
					} else
						dinamicItr++;

				}
				else {
					dinamicItr++;
				}
				
				
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