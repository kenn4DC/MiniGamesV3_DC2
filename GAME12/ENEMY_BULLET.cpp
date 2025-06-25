#include "ENEMY_BULLET.h"

namespace GAME12 {

	ENEMY_BULLET::ENEMY_BULLET(class GAME* game) : BULLET(game) {
		ImgRadius = 40.0f; //80x74
		Shape = CHARACTER::CS_CIRCLE;
		BcRadius = 18;
	}
	ENEMY_BULLET::~ENEMY_BULLET() {
	}
}
