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
		BulletSpeed = width / 2.0f; //2�b�����ĉ�ʂ̍�����E.
		BulletAngSpeed = 3.141592f * 2.0f / 1.0f; //1�b��1��]
		JumpedFlag = false;
		JumpingCount = 0;
		JumpHight = 300.0f;
		JumpAscentTime = 0.5f;
		MaxHp = 1;
		Hp = MaxHp;
		Alive = true;
#if 0
		//����1:VERY_HARD����Z�L�[���������鏈��
		//if (game()->gameMode() == GAME::VERY_HARD_MODE) {
		//	AutoLaunch = false;
		//}
		//else {
		//	AutoLaunch = true;
		//}
#endif
#if 1
		//����2:VERY_HARD�ł��S����
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
			* �W�����v�̊T�O
			* (��) �n�_100����3�b�̎��ō����B�_50�̈ʒu�ɗ��Ē��n����C���[�W
			*  y��-
			*   | 200-50=150
			*   |  +
			*   | + +
			*   |+   +
			*   +     +
			* --0--3--6---- elapse��
			* ����=200
			*
			* ���v�Z�����o��(�������x�[�X)
			*    y = startY + dist / (n*n) * (elapse-n)*(elapse-n) - dist;
			*    y = 200 + 50 / (3*3) * (elapse-3)*(elapse-3) - 50;
			*       elapse=0 ... 200
			*       elapse=3 ... 150
			*       elapse=6 ... 200
			*/
#if 0
			//����1�F2�i�W�����v�܂ŋ���
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
			//����2�F�̂��ꕔ�ł������Ă��ԂȂ炢�ł��W�����v
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
			//��������
			if (game()->gameMode() == GAME::GAME_MODE_HARD) {
				//���̉��ɂ͍s���Ȃ�
				if (Pos.y > height - ImgHeight / 2.0f - 100.0f) {
					Pos.y = height - ImgHeight / 2.0f - 100.0f;
				}
			}
			else if (game()->gameMode() == GAME::GAME_MODE_VERY_HARD) {
				//���̉��ɑ̂����S�ɏ�������Q�[���I�[�o�[
				if (Pos.y > height + ImgHeight / 2.0f) {
					Pos.y = height + ImgHeight / 2.0f;
					Alive = false;
					game()->scene(GAME::SCENE_ID_GAME_OVER)->init();
					game()->changeScene(GAME::SCENE_ID_GAME_OVER);
				}
			}
			else {
				//��logic error.
				__debugbreak();
			}
		}
	}
	void PLAYER::launch() {
		if (true) { //����1: if (AutoLaunch || isPress(KEY_Z)) {
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
		GameOverMoveSpeed = height / 0.5f; //0.5�b�ŉ�ʂ̏ォ�牺.
		Vec = FLOAT2(0.0f, -1.0f);
		//Vec.normalize();
		Alive = true; //���Q�[���I�[�o�[���ɂ̓v���C���[�̉��o���������̂ŕ���������
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
