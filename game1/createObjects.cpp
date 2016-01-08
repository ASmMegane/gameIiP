#include "stdafx.h"
#include "createObjects.h"

int randomNumber(const int & size) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, 32700);
	int number = dist(gen) % size;
	return number;
};


void createShotForHero(GameData & gData) {
	gData.gameSprites["bullet"].spriteItems.emplace_front(gData.gameSprites["bullet"].texture, gData.gameSprites["bullet"].frameSize, gData.gameSprites["bullet"].maxLive);
	auto bulletItr = gData.gameSprites["bullet"].spriteItems.begin();
	auto heroItr = gData.gameSprites["hero"].spriteItems.begin();
	bulletItr->mSprite.signMoveHorizont = 1;
	bulletItr->mSprite.signMoveVertical = 0;
	bulletItr->mSprite.speedKoof = 3;
	bulletItr->sprite.setPosition(heroItr->sprite.getPosition().x + abs(heroItr->sprite.getTextureRect().width), heroItr->sprite.getPosition().y + abs(heroItr->sprite.getTextureRect().height / 2));
}

void createShotForEnemy(GameData & gData, sf::Sprite & spriteEnemy) {
	gData.gameSprites["bulletEnemy"].spriteItems.emplace_front(gData.gameSprites["bulletEnemy"].texture, gData.gameSprites["bulletEnemy"].frameSize, gData.gameSprites["bulletEnemy"].maxLive);
	auto bulletItr = gData.gameSprites["bulletEnemy"].spriteItems.begin();
	bulletItr->mSprite.signMoveHorizont = -1;
	bulletItr->mSprite.signMoveVertical = 0;
	bulletItr->mSprite.speedKoof = 2;
	bulletItr->sprite.setPosition(spriteEnemy.getPosition().x + abs(spriteEnemy.getTextureRect().width / 2), spriteEnemy.getPosition().y + (spriteEnemy.getTextureRect().height / 2));
};


void createExplotion(GameData & gData, const MySpriteDinamics & object, const bool & isBullet) {
	gData.gameSprites["expl"].spriteItems.emplace_front(gData.gameSprites["expl"].texture, gData.gameSprites["expl"].frameSize, gData.gameSprites["expl"].maxLive);
	auto explItr = gData.gameSprites["expl"].spriteItems.begin();
	explItr->mSprite.signMoveHorizont = 0;
	explItr->mSprite.signMoveVertical = 0;
	explItr->mSprite.speedKoof = 1;
	int posX = object.sprite.getPosition().x + abs(object.sprite.getTextureRect().width) / 2 - gData.gameSprites["expl"].frameSize.width / 2;
	int posY = object.sprite.getPosition().y + abs(object.sprite.getTextureRect().height) / 2 - gData.gameSprites["expl"].frameSize.height / 2;
	explItr->sprite.setPosition(posX, posY);
	if (isBullet)
		explItr->sprite.setScale(0.5, 0.5);
};

void createEnemy(GameData & gData, Config & conf, float & timeCreate, std::string const & keyStatic) {
	if (gData.gameSprites[keyStatic].countOfItemsMAX > (int)gData.gameSprites[keyStatic].spriteItems.size()) {
		if (timeCreate <= 0 && (randomNumber(6000)) < 40) {
			gData.gameSprites[keyStatic].spriteItems.emplace_front(gData.gameSprites[keyStatic].texture, gData.gameSprites[keyStatic].frameSize, gData.gameSprites[keyStatic].maxLive);
			gData.gameSprites[keyStatic].spriteItems.begin()->mSprite.speedKoof = (float)((randomNumber(15)) / 10 + 0.8);
			gData.gameSprites[keyStatic].spriteItems.begin()->mSprite.moveTaktik = 1;
			gData.gameSprites[keyStatic].spriteItems.begin()->mSprite.signMoveHorizont = -1;
			gData.gameSprites[keyStatic].spriteItems.begin()->mSprite.signMoveVertical = 0;
			gData.gameSprites[keyStatic].spriteItems.begin()->sprite.setPosition((float)(gData.window.getSize().x - 1), (float)(randomNumber(gData.window.getSize().y - gData.gameSprites["enemy1"].frameSize.width)) + 1);
			timeCreate = conf.timeDistanceCreate;
		}
	}
}
