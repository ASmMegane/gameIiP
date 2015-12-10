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
	gData.gameSprites["hero"].maxLive = 100;
	gData.gameSprites["hero"].spriteItems.push_front(MySpriteDinamics(gData.gameSprites["hero"].texture, gData.gameSprites["hero"].frameSize, gData.gameSprites["hero"].maxLive));
	gData.gameSprites["hero"].isFlyOutOfScreen = false;
	gData.gameSprites["hero"].spriteItems.begin()->mSprite.moveTaktik = 0;
	gData.gameSprites["hero"].spriteItems.begin()->mSprite.speedKoof = 1;
	gData.gameSprites["hero"].spriteItems.begin()->mSprite.signMoveHorizont = 0;
	gData.gameSprites["hero"].spriteItems.begin()->mSprite.signMoveVertical = 0;
	gData.gameSprites["hero"].spriteItems.begin()->sprite.setPosition(0, gData.window.getSize().y / 2 - gData.gameSprites["hero"].frameSize.height / 2);

	Img.loadFromFile(conf.imageEnemy1);
	Img.createMaskFromColor(Img.getPixel(0, 0));
	gData.gameSprites["enemy1"].texture.loadFromImage(Img);
	gData.gameSprites["enemy1"].baseTPF = sf::milliseconds(1000 / 6.0);
	gData.gameSprites["enemy1"].frameCount = 6;
	gData.gameSprites["enemy1"].frameSize.height = gData.gameSprites["enemy1"].texture.getSize().y;
	gData.gameSprites["enemy1"].frameSize.width = gData.gameSprites["enemy1"].texture.getSize().x / gData.gameSprites["enemy1"].frameCount;
	gData.gameSprites["enemy1"].baseSpeedPx = 0.0003;
	gData.gameSprites["enemy1"].countOfItemsMAX = 10;
	gData.gameSprites["enemy1"].maxLive = 4;
	gData.gameSprites["enemy1"].isFlyOutOfScreen = true;

	Img.loadFromFile(conf.imageEnemy2);
	Img.createMaskFromColor(Img.getPixel(0, 0));
	gData.gameSprites["enemy2"].texture.loadFromImage(Img);
	gData.gameSprites["enemy2"].baseTPF = sf::milliseconds(1000 / 6.0);
	gData.gameSprites["enemy2"].frameCount = 6;
	gData.gameSprites["enemy2"].frameSize.height = gData.gameSprites["enemy2"].texture.getSize().y;
	gData.gameSprites["enemy2"].frameSize.width = gData.gameSprites["enemy2"].texture.getSize().x / gData.gameSprites["enemy2"].frameCount;
	gData.gameSprites["enemy2"].baseSpeedPx = 0.0003;
	gData.gameSprites["enemy2"].countOfItemsMAX = 3;
	gData.gameSprites["enemy2"].maxLive = 8;
	gData.gameSprites["enemy2"].isFlyOutOfScreen = true;

	Img.loadFromFile(conf.imageBulett1);
	Img.createMaskFromColor(Img.getPixel(0, 0));
	gData.gameSprites["bullet"].texture.loadFromImage(Img);
	gData.gameSprites["bullet"].baseTPF = sf::milliseconds(1000 / 6.0);
	gData.gameSprites["bullet"].frameCount = 4;
	gData.gameSprites["bullet"].frameSize.height = gData.gameSprites["bullet"].texture.getSize().y;
	gData.gameSprites["bullet"].frameSize.width = gData.gameSprites["bullet"].texture.getSize().x / gData.gameSprites["bullet"].frameCount;
	gData.gameSprites["bullet"].baseSpeedPx = 0.0003;
	gData.gameSprites["bullet"].countOfItemsMAX = 0;
	gData.gameSprites["bullet"].maxLive = 2;
	gData.gameSprites["bullet"].isFlyOutOfScreen = true;

	Img.loadFromFile(conf.imageExplotion);
	Img.createMaskFromColor(Img.getPixel(0, 0));
	gData.gameSprites["expl"].texture.loadFromImage(Img);
	gData.gameSprites["expl"].baseTPF = sf::milliseconds(1000 / 30.0);
	gData.gameSprites["expl"].frameCount = 12;
	gData.gameSprites["expl"].frameSize.height = gData.gameSprites["expl"].texture.getSize().y;
	gData.gameSprites["expl"].frameSize.width = gData.gameSprites["expl"].texture.getSize().x / gData.gameSprites["expl"].frameCount;
	gData.gameSprites["expl"].baseSpeedPx = 0;
	gData.gameSprites["expl"].countOfItemsMAX = 0;
	gData.gameSprites["expl"].maxLive = 0;
	gData.gameSprites["expl"].isFlyOutOfScreen = true;
	gData.gameSprites["expl"].isCycleFrames = false;


	gData.backeTexture.loadFromImage(conf.backeImg);
	gData.backeG1.setTexture(gData.backeTexture);
	gData.backeG2.setTexture(gData.backeTexture);
	gData.backeRect.height = conf.backeImg.getSize().y;
	gData.backeRect.width = conf.backeImg.getSize().x;
	gData.backeG2.setTextureRect(sf::IntRect(gData.backeRect.width, 0, -gData.backeRect.width, gData.backeRect.height));
	gData.backeG1.setScale(3.1, 3.1);
	gData.backeG2.setScale(3.1, 3.1);

}

