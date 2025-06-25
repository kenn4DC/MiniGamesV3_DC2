#include "../../libOne/inc/libOne.h"
#include "BULLET.h"

namespace GAME12 {

	BULLET::BULLET(class GAME* game) : CHARACTER(game) {
	}
	BULLET::~BULLET() {
	}
	void BULLET::init() {
		Pos.init();
		Vec.init();
		Speed = 0;
		AngSpeed = 0;
		Scale = 1.0f;
		MaxHp = 1;
		Hp = MaxHp;
		Alive = false;
	}
	void BULLET::update() {
		if (Alive) {
			Pos += Vec * Speed * delta;
			Angle += AngSpeed * delta;
			if (Pos.x < -ImgRadius || Pos.x > width + ImgRadius || Pos.y < -ImgRadius || Pos.y > height + ImgRadius){
				init();
			}
		}
	}
	void BULLET::launch(const FLOAT2& pos, const FLOAT2& vec, float speed, float angSpeed) {
		if (!Alive) {
			Pos = pos;
			Vec = vec;
			Speed = speed;
			AngSpeed = angSpeed;

			Alive = true;
		}
		else {
			//WARNING(true, "logic error(Alive is already true).", "");
			__debugbreak();
		}
	}
	void BULLET::damage() {
		init();
	}
}