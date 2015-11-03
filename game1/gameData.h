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

struct Config
{
	std::string imageAdres = "image/heroFly.png";	
	std::string imageBacke = "image/backeGraund.jpg";
	sf::Image backeImg;
};

struct MySpriteDinamics 
{
	MySpriteDinamics(sf::Texture &texture) { frameCurrent = 0; frameChangeTime = sf::microseconds(0); sprite.setTexture(texture); };
	sf::Sprite sprite;
	int frameCurrent;
	sf::Time frameChangeTime;
};

struct MySpriteStatics
{
	sf::Texture texture;
	sf::IntRect frameSize;
	int frameCount;
	sf::Time baseTPF;
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

