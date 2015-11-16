
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <random>
#include <ctime>
#include <windows.h>
#include "gameData.h"


void ConfigPrepare(Config & conf)
{	
	conf.backeImg.loadFromFile(conf.imageBacke);
	
};

void gameInitializeSprite(Config & conf, GameData & gData)
{
	gData.window.create(sf::VideoMode(800, 600), "Game");

	sf::Image Img;
	Img.loadFromFile(conf.imageAdres);
	Img.createMaskFromColor(Img.getPixel(0, 0));
	gData.gameSprites["hero"].texture.loadFromImage(Img);
	gData.gameSprites["hero"].baseTPF = sf::milliseconds(1000/6.0);
	gData.gameSprites["hero"].frameCount = 4;
	gData.gameSprites["hero"].frameSize.height = gData.gameSprites["hero"].texture.getSize().y;
	gData.gameSprites["hero"].frameSize.width = gData.gameSprites["hero"].texture.getSize().x / gData.gameSprites["hero"].frameCount;
	gData.gameSprites["hero"].baseSpeedPx = 0.0003;
	gData.gameSprites["hero"].countOfItemsMAX = 0;
	gData.gameSprites["hero"].spriteItems.push_front(MySpriteDinamics(gData.gameSprites["hero"].texture));
	gData.gameSprites["hero"].isFlyOutOfScreen = false;
	gData.gameSprites["hero"].spriteItems.begin()->mSprite.moveTaktik = 0;
	gData.gameSprites["hero"].spriteItems.begin()->mSprite.speedKoof = 1;
	gData.gameSprites["hero"].spriteItems.begin()->mSprite.signMoveHorizont = 0;
	gData.gameSprites["hero"].spriteItems.begin()->mSprite.signMoveVertical = 0;

	Img.loadFromFile(conf.imageEnemy1);
	Img.createMaskFromColor(Img.getPixel(0, 0));
	gData.gameSprites["enemy1"].texture.loadFromImage(Img);
	gData.gameSprites["enemy1"].baseTPF = sf::milliseconds(1000 / 6.0);
	gData.gameSprites["enemy1"].frameCount = 6;
	gData.gameSprites["enemy1"].frameSize.height = gData.gameSprites["enemy1"].texture.getSize().y;
	gData.gameSprites["enemy1"].frameSize.width = gData.gameSprites["enemy1"].texture.getSize().x / gData.gameSprites["enemy1"].frameCount;
	gData.gameSprites["enemy1"].baseSpeedPx = 0.0003;
	gData.gameSprites["enemy1"].countOfItemsMAX = 5;
	gData.gameSprites["enemy1"].isFlyOutOfScreen = true;

	gData.backeTexture.loadFromImage(conf.backeImg);
	gData.backeG1.setTexture(gData.backeTexture);
	gData.backeG2.setTexture(gData.backeTexture);	
	gData.backeRect.height = conf.backeImg.getSize().y;
	gData.backeRect.width = conf.backeImg.getSize().x;	
	gData.backeG2.setTextureRect(sf::IntRect(gData.backeRect.width, 0, -gData.backeRect.width, gData.backeRect.height));
	gData.backeG1.setScale(3.1, 3.1);
	gData.backeG2.setScale(3.1, 3.1);
	
};

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
			if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)) { gData.gameSprites["hero"].spriteItems.begin()->mSprite.signMoveHorizont = -1; }
			if ((event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Left)) { gData.gameSprites["hero"].spriteItems.begin()->mSprite.signMoveHorizont = 0; }
			if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)) { gData.gameSprites["hero"].spriteItems.begin()->mSprite.signMoveHorizont = 1; }
			if ((event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Right)) { gData.gameSprites["hero"].spriteItems.begin()->mSprite.signMoveHorizont = 0; }
			if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)) { gData.gameSprites["hero"].spriteItems.begin()->mSprite.signMoveVertical = 1; }
			if ((event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Down)) { gData.gameSprites["hero"].spriteItems.begin()->mSprite.signMoveVertical = 0; }
			if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)) { gData.gameSprites["hero"].spriteItems.begin()->mSprite.signMoveVertical = -1; }
			if ((event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Up)) { gData.gameSprites["hero"].spriteItems.begin()->mSprite.signMoveVertical = 0; }

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
				if (timeCreate <= 0) {
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
				} else {
					dinamicItr->mSprite.signMoveHorizont = 0;
					dinamicItr->mSprite.signMoveVertical = 0;
				}
				if (dinamicItr->sprite.getPosition().x < -staticItr->second.frameSize.width) {
					dinamicItr = staticItr->second.spriteItems.erase(dinamicItr);
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