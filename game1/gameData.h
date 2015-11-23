#pragma once
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <list>
#include <random>
#include <string>
#include <ctime>
#include <windows.h>
#include <map>

struct Config {
	std::string imageAdres = "image/heroFly.png";	
	std::string imageBacke = "image/backeGraund.jpg";
	std::string imageEnemy1 = "image/enemy1.png";
	std::string imageBulett1 = "image/bulett1.png";
	sf::Image backeImg;
	const float timeDistanceCreate = 100000;
};

struct moveingSprite {
	float speedKoof;
	int moveTaktik;
	int signMoveHorizont;
	int signMoveVertical;
};

struct MySpriteDinamics 
{
	MySpriteDinamics(sf::Texture & texture) { 
		frameCurrent = 0; frameChangeTime = sf::microseconds(0); sprite.setTexture(texture); spriteHeal = 100;};
	sf::Sprite sprite;
	int frameCurrent;
	sf::Time frameChangeTime;
	int spriteHeal;
	bool isVisibalSprite;
	moveingSprite mSprite;
};

struct MySpriteStatics
{
	sf::Texture texture;
	sf::IntRect frameSize;
	int frameCount;
	int countOfItemsMAX;
	sf::Time baseTPF;
	float baseSpeedPx;
	bool isFlyOutOfScreen;
	std::list <MySpriteDinamics> spriteItems;
};

struct GameData 
{
	sf::RenderWindow window;
	sf::Texture backeTexture;
	sf::Sprite  backeG1;
	sf::Sprite  backeG2;
	sf::IntRect backeRect;
	std::map <std::string, MySpriteStatics> gameSprites;
};

