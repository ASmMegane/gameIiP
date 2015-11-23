#include <stdafx.h>
#include "gameInit.h"

void gameInitializeSprite(Config & conf, GameData & gData) {
	gData.window.create(sf::VideoMode(800, 600), "Game");

	sf::Image Img;
	Img.loadFromFile(conf.imageAdres);
	Img.createMaskFromColor(Img.getPixel(0, 0));
	gData.gameSprites["hero"].texture.loadFromImage(Img);
	gData.gameSprites["hero"].baseTPF = sf::milliseconds(1000 / 6.0);
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
	gData.gameSprites["enemy1"].countOfItemsMAX = 10;
	gData.gameSprites["enemy1"].isFlyOutOfScreen = true;

	Img.loadFromFile(conf.imageBulett1);
	Img.createMaskFromColor(Img.getPixel(0, 0));
	gData.gameSprites["bullet"].texture.loadFromImage(Img);
	gData.gameSprites["bullet"].baseTPF = sf::milliseconds(1000 / 6.0);
	gData.gameSprites["bullet"].frameCount = 4;
	gData.gameSprites["bullet"].frameSize.height = gData.gameSprites["bullet"].texture.getSize().y;
	gData.gameSprites["bullet"].frameSize.width = gData.gameSprites["bullet"].texture.getSize().x / gData.gameSprites["bullet"].frameCount;
	gData.gameSprites["bullet"].baseSpeedPx = 0.0003;
	gData.gameSprites["bullet"].countOfItemsMAX = 0;
	gData.gameSprites["bullet"].isFlyOutOfScreen = true;

	gData.backeTexture.loadFromImage(conf.backeImg);
	gData.backeG1.setTexture(gData.backeTexture);
	gData.backeG2.setTexture(gData.backeTexture);
	gData.backeRect.height = conf.backeImg.getSize().y;
	gData.backeRect.width = conf.backeImg.getSize().x;
	gData.backeG2.setTextureRect(sf::IntRect(gData.backeRect.width, 0, -gData.backeRect.width, gData.backeRect.height));
	gData.backeG1.setScale(3.1, 3.1);
	gData.backeG2.setScale(3.1, 3.1);

}

