#include "../../libOne/inc/libOne.h"
#include "GAME12.h"
#include "CHARACTER.h"
#include "BULLETS_MANAGER.h"
#include "ENEMY.h"

namespace GAME12 {

	ENEMY::ENEMY(class GAME* game) : CHARACTER(game) {
	}
	ENEMY::~ENEMY() {
	}
	void ENEMY::init(float px, float py) {
		Pos = FLOAT2(px, py);
		Scale = 1.0f;
		BulletLaunchInterval = 2.0f;
		BulletLaunchRestTime = BulletLaunchInterval;
		BulletSpeed = 1300.0f;
		MoveAngle = 180.0f;
		MoveAngSpeed = 3.141592f * 2.0f / 3.0f; //3•b‚©‚¯‚ÄÅ‰‚É–ß‚é
		MoveRadius = 150.0f;
		if (game()->gameMode() == GAME::GAME_MODE_NORMAL) {
			MaxHp = 15;
		}
		else if (game()->gameMode() == GAME::GAME_MODE_HARD) {
			MaxHp = 20;
		}
		else {
			MaxHp = 25;
		}
		Hp = MaxHp;
		Alive = true;
	}
	void ENEMY::update() {
		if (Alive) {
			move();
			launch();
			Scale = (Hp/2.0f + MaxHp/2.0f) / MaxHp; //Scale‚ð1.0f`0.5f‚É’²®‚·‚é
		}
	}
	void ENEMY::move() {
		MoveAngle += MoveAngSpeed * delta;
		Pos.y = CenterPosY + sinf(MoveAngle) * MoveRadius;
	}
	void ENEMY::launch() {
		if (BulletLaunchRestTime == BulletLaunchInterval) {
			FLOAT2 vec = FLOAT2(-1.0f, 0.0f);
			//vec.normalize();
			game()->enemiesBulletsManager()->launch(Pos,vec, BulletSpeed, 0.0f);
		}
		BulletLaunchRestTime -= delta;
		if (BulletLaunchRestTime < 0) {
			BulletLaunchRestTime = BulletLaunchInterval;
		}
	}
	void ENEMY::setCenterPosY(float y) {
		CenterPosY = y;
	}
	void ENEMY::damage() {
		Hp -= 1;
		if (Hp <= 0) {
			Alive = false;
		}
	}
}