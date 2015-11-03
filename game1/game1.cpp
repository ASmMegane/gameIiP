
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
	gData.gameSprites["hero"].spriteItems.push_front(MySpriteDinamics(gData.gameSprites["hero"].texture));

	
	gData.backeTexture.loadFromImage(conf.backeImg);
	gData.backeG1.setTexture(gData.backeTexture);
	gData.backeG2.setTexture(gData.backeTexture);	
	gData.backeRect.height = conf.backeImg.getSize().y;
	gData.backeRect.width = conf.backeImg.getSize().x;	
	gData.backeG2.setTextureRect(sf::IntRect(gData.backeRect.width, 0, -gData.backeRect.width, gData.backeRect.height));
	gData.backeG1.scale(sf::Vector2f(3.1f, 3.1f));
	gData.backeG2.scale(sf::Vector2f(3.1f, 3.1f));
	
};

void GameRun(Config & conf, GameData & gData)
{
	sf::Clock clock;

	while (gData.window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		sf::Event event;
		while (gData.window.pollEvent(event))
		{			
			if (event.type == sf::Event::Closed ||
				(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
				gData.window.close();
		}

		if ((gData.backeG1.getPosition().x < 0) && (gData.backeG1.getPosition().x > -1)) {gData.backeG2.setPosition(800,0); }
		if ((gData.backeG2.getPosition().x < 0) && (gData.backeG2.getPosition().x > -1)) {gData.backeG1.setPosition(800,0); }
		gData.backeG1.move(-0.0001*time, 0);
		gData.backeG2.move(-0.0001*time, 0);

		std::list <MySpriteDinamics>::iterator heroItr;
		heroItr = gData.gameSprites["hero"].spriteItems.begin();
		heroItr->frameChangeTime += sf::microseconds(time);
		if (heroItr->frameChangeTime >= gData.gameSprites["hero"].baseTPF) {
			int frameInc = (heroItr->frameChangeTime / gData.gameSprites["hero"].baseTPF);
			heroItr->frameCurrent += frameInc;
			heroItr->frameCurrent = heroItr->frameCurrent % gData.gameSprites["hero"].frameCount;
			heroItr->frameChangeTime -= sf::microseconds(frameInc * gData.gameSprites["hero"].baseTPF.asMicroseconds());
		}

		heroItr->sprite.setTextureRect(sf::IntRect(gData.gameSprites["hero"].frameSize.width * (heroItr->frameCurrent + 1), 0, -gData.gameSprites["hero"].frameSize.width, gData.gameSprites["hero"].frameSize.height));
		
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && heroItr->sprite.getPosition().x > 0) { heroItr->sprite.move(-0.001*time, 0); }
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && heroItr->sprite.getPosition().x < (gData.window.getSize().x - gData.gameSprites["hero"].frameSize.width)) { heroItr->sprite.move(0.001*time, 0); }
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && heroItr->sprite.getPosition().y > 0) { heroItr->sprite.move(0, -0.001*time); }
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && heroItr->sprite.getPosition().y < (gData.window.getSize().y - gData.gameSprites["hero"].frameSize.height)) { heroItr->sprite.move(0, 0.001*time); }
				
		gData.window.clear();
		gData.window.draw(gData.backeG1);
		gData.window.draw(gData.backeG2);
		gData.window.draw(heroItr->sprite);
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