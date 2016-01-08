#include "stdafx.h"
#include "moveBackG.h"

void moveBackG(GameData & gData, bool & flagBG) {
	if ((gData.backeG1.getPosition().x <= 0) && (flagBG)) {
		gData.backeG2.setPosition(800, 0);
		flagBG = false;
	}
	if ((gData.backeG2.getPosition().x <= 0) && (!(flagBG))) {
		gData.backeG1.setPosition(800, 0);
		flagBG = true;
	}
	gData.backeG1.move(-2, 0);
	gData.backeG2.move(-2, 0);
}