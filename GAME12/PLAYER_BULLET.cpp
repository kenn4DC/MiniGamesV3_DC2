#include "PLAYER_BULLET.h"

namespace GAME12 {

	PLAYER_BULLET::PLAYER_BULLET(class GAME* game) : BULLET(game) {
		ImgRadius = 32.0f; //64x61
		AngSpeed = 0.0f;
		Shape = CHARACTER::CS_CIRCLE;
		BcRadius = 14.0f;
	}
	PLAYER_BULLET::~PLAYER_BULLET() {
	}

}