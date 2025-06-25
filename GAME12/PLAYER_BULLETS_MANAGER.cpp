#include "../../libOne/inc/libOne.h"
#include "FLOAT2.h"
#include "PLAYER_BULLET.h"
#include "PLAYER_BULLETS_MANAGER.h"

namespace GAME12 {
	PLAYER_BULLETS_MANAGER::PLAYER_BULLETS_MANAGER(class GAME* game) : BULLETS_MANAGER(game){}

	void PLAYER_BULLETS_MANAGER::create() {
		TotalNum = 50;
		Bullets = new BULLET * [TotalNum] {};
		for (int i = 0; i < TotalNum; i++) {
			Bullets[i] = new PLAYER_BULLET(game());
		}

		int img = loadImage("../MAIN/assets/game12/pBullet.png");
		for (int i = 0; i < TotalNum; i++) {
			bullet(i)->setImg(img);
			//bullet(i)->setBoundingBoxFlag(true);
		}
	}
	void PLAYER_BULLETS_MANAGER::launch(const class FLOAT2& pos, const class FLOAT2& vec, float speed, float angSpeed) {
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