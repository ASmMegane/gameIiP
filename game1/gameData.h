#pragma once
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <random>
#include <ctime>
#include <windows.h>

struct Config
{
	std::string imageAdres = "image/enemy.png";
	sf::Image heroImg;
	std::string imageBacke = "image/backeGraund.jpg";
	sf::Image backeImg;
};

struct GameData
{
	sf::RenderWindow window;
	sf::Texture heroTexture;
	sf::Sprite  hero;
	sf::IntRect heroRect;
	sf::Texture backeTexture;
	sf::Sprite  backeG1;
	sf::Sprite  backeG2;
	sf::IntRect backeRect;

};
