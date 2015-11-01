
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
	conf.heroImg.loadFromFile(conf.imageAdres);
	conf.backeImg.loadFromFile(conf.imageBacke);
};

void gameInitializeSprite(Config & conf, GameData & gData)
{
	gData.window.create(sf::VideoMode(800, 600), "Game");

	gData.heroTexture.loadFromImage(conf.heroImg);
	gData.hero.setTexture(gData.heroTexture);
	gData.heroRect.height = conf.heroImg.getSize().y;
	gData.heroRect.width = conf.heroImg.getSize().x;
	gData.hero.setTextureRect(sf::IntRect(gData.heroRect.width, 0, -gData.heroRect.width, gData.heroRect.height));

	
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

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && gData.hero.getPosition().x > 0) { gData.hero.move(-0.001*time, 0); (gData.hero.setTextureRect(sf::IntRect(gData.heroRect.width, 0, -gData.heroRect.width, gData.heroRect.height))); }
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && gData.hero.getPosition().x < (gData.window.getSize().x - conf.heroImg.getSize().x)) { gData.hero.move(0.001*time, 0); (gData.hero.setTextureRect(sf::IntRect(gData.heroRect.width, 0, -gData.heroRect.width, gData.heroRect.height))); }
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && gData.hero.getPosition().y > 0) { gData.hero.move(0, -0.001*time); (gData.hero.setTextureRect(sf::IntRect(gData.heroRect.width, 0, -gData.heroRect.width, gData.heroRect.height))); }
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && gData.hero.getPosition().y < (gData.window.getSize().y - conf.heroImg.getSize().y)) { gData.hero.move(0, 0.001*time); (gData.hero.setTextureRect(sf::IntRect(gData.heroRect.width, 0, -gData.heroRect.width, gData.heroRect.height))); }


		
		gData.window.clear();
		gData.window.draw(gData.backeG1);
		gData.window.draw(gData.backeG2);
		gData.window.draw(gData.hero);
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