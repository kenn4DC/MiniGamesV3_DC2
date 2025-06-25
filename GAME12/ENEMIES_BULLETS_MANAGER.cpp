#include "../../libOne/inc/libOne.h"
#include "ENEMY_BULLET.h"
#include "ENEMIES_BULLETS_MANAGER.h"

namespace GAME12 {

	ENEMIES_BULLETS_MANAGER::ENEMIES_BULLETS_MANAGER(class GAME* game) : BULLETS_MANAGER(game) {}

	void ENEMIES_BULLETS_MANAGER::create() {
		TotalNum = 50;
		Bullets = new BULLET * [TotalNum] {};
		for (int i = 0; i < TotalNum; i++) {
			Bullets[i] = new ENEMY_BULLET(game());
		}

		int img = loadImage("../MAIN/assets/game12/eBullet.png");
		for (int i = 0; i < TotalNum; i++) {
			bullet(i)->setImg(img);
			//bullet(i)->setBoundingBoxFlag(true);
		}

	}
	void ENEMIES_BULLETS_MANAGER::launch(const class FLOAT2& pos, const class FLOAT2& vec, float speed, float angSpeed) {
		int i;
		for (i = 0; i < TotalNum; i++) {
			if (!bullet(i)->alive()) {
				bullet(i)->launch(pos, vec, speed, angSpeed);
				break;
			}
		}
		if (i >= TotalNum) {
			//WARNING(true, "Player bullet num over!!", "");
			__debugbreak();
		}
	}

}