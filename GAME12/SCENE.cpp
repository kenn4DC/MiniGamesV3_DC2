#include "../../libOne/inc/libOne.h"
#include "SCENE.h"
#include "TITLE.h"

namespace GAME12 {
	SCENE::SCENE(GAME* game) : GAME_OBJECT(game)
	{
	}
	SCENE::~SCENE()
	{
	}
	void SCENE::create() {}
	void SCENE::init() {}
	void SCENE::proc() {
		clear();
		update();
		draw();
		nextScene();
	}
	void SCENE::update() {}
	void SCENE::draw() {}
	void SCENE::nextScene() {}
}
