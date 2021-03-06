//
//Spring.cpp
//

#include "Spring.h";
#include "EventCollision.h";
#include "Player.h";
#include "Cube.h";
#include "ResourceManager.h";
#include "LogManager.h";

Spring::Spring(float inten) {
	setCentered(false);

	df::Sprite *p_temp_sprite;
	p_temp_sprite = RM.getSprite("spring");
	if (!p_temp_sprite)
		LM.writeLog("Cube::Cube(): Warning! Sprite '%s' not found", "ship");
	else {
		setSprite(p_temp_sprite, true);
		setSpriteSlowdown(0);
	}

	setAltitude(3);

	// Set object type.
	setType("Spring");
	intensity = inten;

	setSolidness(df::SOFT);
}

//Handles Events
int Spring::eventHandler(const df::Event *p_e) {
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision *p_c = dynamic_cast <const df::EventCollision *> (p_e);
		df::EventCollision *c = const_cast<df::EventCollision *>(p_c);
		if (c->getObject1()->getType() == "Cube") {
			Cube *cub = reinterpret_cast < Cube *> (c->getObject1());
			cub->setVerticalSpeed(intensity);
			df::Sound *p_sound = df::ResourceManager::getInstance().getSound("spring");
			p_sound->play();
			return 1;
		}
		else if (c->getObject1()->getType() == "Player") {
			Player *pl = reinterpret_cast <Player *> (c->getObject1());
			pl->setVerticalSpeed(intensity);
			pl->jump();
			df::Sound *p_sound = df::ResourceManager::getInstance().getSound("spring");
			p_sound->play();
			return 1;
		}
	}
	return 0;
}

//Sets intensity
void Spring::setIntensity(float inten) {
	intensity = inten;
}