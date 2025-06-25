#include "../../libOne/inc/libOne.h"
#include "SCENE.h"
#include "GAME12.h"
#include "CHARACTER.h"
#include "PLAYER_BULLETS_MANAGER.h"
#include "PLAYER.h"

namespace GAME12 {

	PLAYER::PLAYER(class GAME* game) : CHARACTER(game) {
	}
	PLAYER::~PLAYER() {
	}
	void PLAYER::create() {
		int img = loadImage("../MAIN/assets/game12/player.png");
		Img = img;
		ImgWidth = 128.0f;
		ImgHeight = 209.0f;
		Shape = CHARACTER::CS_AABB;
		BbWidth = 84;
		BbHeight = 190;

		//BoundingBoxFlag = true;
	}
	void PLAYER::init() {
		Pos = FLOAT2(200.0f ,height - ImgHeight / 2.0f - 100.0f);
		Speed = height / 1.5f;
		Angle = 0.0f;
		Scale = 1.0f;
		BulletLaunchInterval = 0.15f;
		BulletLaunchRestTime = BulletLaunchInterval;
		BulletSpeed = width / 2.0f; //2秒かけて画面の左から右.
		BulletAngSpeed = 3.141592f * 2.0f / 1.0f; //1秒で1回転
		JumpedFlag = false;
		JumpingCount = 0;
		JumpHight = 300.0f;
		JumpAscentTime = 0.5f;
		MaxHp = 1;
		Hp = MaxHp;
		Alive = true;
#if 0
		//★案1:VERY_HARD時にZキーを押させる処理
		//if (game()->gameMode() == GAME::VERY_HARD_MODE) {
		//	AutoLaunch = false;
		//}
		//else {
		//	AutoLaunch = true;
		//}
#endif
#if 1
		//★案2:VERY_HARDでも全自動
		AutoLaunch = true;
#endif
	}
	void PLAYER::update() {
		if (Alive) {
			move();
			launch();
		}
	}
	void PLAYER::move() {
		if (game()->gameMode() == GAME::GAME_MODE_NORMAL) {
			moveUpDown();
		}
		else {
			moveJump();
		}
	}
	void PLAYER::moveUpDown() {
		if (isPress(KEY_W)) {
			float upLimitY = 0 + ImgHeight / 2.0f + 100.0f;
			Pos.y -= Speed * delta;
			if (Pos.y < upLimitY) {
				Pos.y = upLimitY;
			}
		}
		if (isPress(KEY_S)) {
			float downLimitY = height - ImgHeight / 2.0f - 100.0f;
			Pos.y += Speed * delta;
			if (Pos.y > downLimitY) {
				Pos.y = downLimitY;
			}
		}
	}
	void PLAYER::moveJump() {
		if (isTrigger(KEY_SPACE)) {
			/*
			* ジャンプの概念
			* (例) 始点100から3秒の時最高到達点50の位置に来て着地するイメージ
			*  y軸-
			*   | 200-50=150
			*   |  +
			*   | + +
			*   |+   +
			*   +     +
			* --0--3--6---- elapse軸
			* 高さ=200
			*
			* ★計算式を出す(放物線ベース)
			*    y = startY + dist / (n*n) * (elapse-n)*(elapse-n) - dist;
			*    y = 200 + 50 / (3*3) * (elapse-3)*(elapse-3) - 50;
			*       elapse=0 ... 200
			*       elapse=3 ... 150
			*       elapse=6 ... 200
			*/
#if 0
			//★案1：2段ジャンプまで許可
			if (JumpingCount < 2) {
				bool inTime = JumpingTime > JumpAscentTime - 0.15f && JumpingTime <= JumpAscentTime + 0.15f;
				if ((JumpingCount == 0) || (JumpingCount != 0 && inTime)) {
					JumpingCount++;
					JumpingTime = 0.0f;
					JumpedPosY = Pos.y;
				}
			}
#endif;
#if 1
			//★案2：体が一部でも見えてる状態ならいつでもジャンプ
			if (Pos.y + ImgHeight / 2.0f > 0.0f) {
				JumpedFlag = true;
				JumpingCount++;
				JumpingTime = 0.0f;
				JumpedPosY = Pos.y;
			}
#endif
		}
		if (JumpingCount) {
			JumpingTime += delta;
			float a = JumpHight / (JumpAscentTime * JumpAscentTime);
			float b = JumpingTime - JumpAscentTime;
			Pos.y = JumpedPosY + a * (b * b) - JumpHight;
			//落下判定
			if (game()->gameMode() == GAME::GAME_MODE_HARD) {
				//床の下には行かない
				if (Pos.y > height - ImgHeight / 2.0f - 100.0f) {
					Pos.y = height - ImgHeight / 2.0f - 100.0f;
				}
			}
			else if (game()->gameMode() == GAME::GAME_MODE_VERY_HARD) {
				//床の下に体が完全に消えたらゲームオーバー
				if (Pos.y > height + ImgHeight / 2.0f) {
					Pos.y = height + ImgHeight / 2.0f;
					Alive = false;
					game()->scene(GAME::SCENE_ID_GAME_OVER)->init();
					game()->changeScene(GAME::SCENE_ID_GAME_OVER);
				}
			}
			else {
				//★logic error.
				__debugbreak();
			}
		}
	}
	void PLAYER::launch() {
		if (true) { //★案1: if (AutoLaunch || isPress(KEY_Z)) {
			if (BulletLaunchRestTime == BulletLaunchInterval) {
				FLOAT2 vec(1.0f, 0.0f);
				//vec.normalize();
				game()->playerBulletsManager()->launch(Pos, vec, BulletSpeed, BulletAngSpeed);
			}
			BulletLaunchRestTime -= delta;
			if (BulletLaunchRestTime < 0) {
				BulletLaunchRestTime = BulletLaunchInterval;
			}
		}
		else {
			BulletLaunchRestTime = BulletLaunchInterval;
		}
	}
	void PLAYER::damage() {
		Alive = false;
	}
	bool PLAYER::jumpedFlag() {
		return JumpedFlag;
	}
	void PLAYER::gameOverInit() {
		GameOverMoveSpeed = height / 0.5f; //0.5秒で画面の上から下.
		Vec = FLOAT2(0.0f, -1.0f);
		//Vec.normalize();
		Alive = true; //★ゲームオーバー時にはプレイヤーの演出をしたいので復活させる
	}
	void PLAYER::gameOverUpdate() {
		Pos.y += Vec.y * GameOverMoveSpeed * delta;
		if (Pos.y < 0 + ImgWidth) {
			Vec.y *= -1;
			Pos.y = 0 + ImgWidth;
			Angle = 3.141592f;
		}
		if (Pos.y > height + ImgHeight / 2.0f) {
			Alive = false;
		}
	}
	void PLAYER::gameClearInit() {
		Pos = FLOAT2(width / 2.0f, height / 2.0f - 100.0f);
		Scale = 1.0f;
	}
	void PLAYER::gameClearUpdate() {
		Scale += 0.025f * delta;
	}
}
