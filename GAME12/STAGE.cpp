#include "../../libOne/inc/libOne.h"
#include "SCENE.h"
#include "PLAYER.h"
#include "ENEMIES_MANAGER.h"
#include "PLAYER_BULLETS_MANAGER.h"
#include "ENEMIES_BULLETS_MANAGER.h"
#include "BLOCK.h"
#include "COLLISION.h"
#include "GAME12.h"
#include "STAGE.h"

namespace GAME12 {

	STAGE::STAGE(class GAME* game) : SCENE(game) {
	}
	STAGE::~STAGE() {
	}
	void STAGE::init() {
		DebugStop = false;
		if (game()->gameMode() == GAME::GAME_MODE_NORMAL) {
			LimitTime = 60; //20�b�����ōs����
		}
		else if (game()->gameMode() == GAME::GAME_MODE_HARD) {
			LimitTime = 50; //20�b�����ōs����
		}
		else if (game()->gameMode() == GAME::GAME_MODE_VERY_HARD) {
			LimitTime = 40; //1��:25.76�b, 2��:29.29�b, 3��:30.62�b�ŃN���A���т���!!!
		}
		else {
			//��Logic error.
			__debugbreak();
		}
		Time = 0;

		game()->player()->init();
		game()->enemiesManager()->init();
		game()->playerBulletsManager()->init();
		game()->enemiesBulletsManager()->init();
	}
	void STAGE::update() {
		//��T�L�[�ɂ��X�g�b�v����(clear() & draw() �͍s��)
		if (isTrigger(KEY_T)) {
			DebugStop = !DebugStop;
		}
		if (DebugStop) {
			return;
		}
		//�����N���A
		if (isTrigger(KEY_P)) {
			game()->setGameTime(Time);
			game()->scene(GAME::SCENE_ID_GAME_CLEAR)->init();
			game()->changeScene(GAME::SCENE_ID_GAME_CLEAR);
		}
		Time += delta;

		game()->player()->update();
		game()->enemiesManager()->update();
		game()->playerBulletsManager()->update();
		game()->enemiesBulletsManager()->update();

		game()->collision()->playerBulletsVsEnemies();
		game()->collision()->enemiesBulletsVsPlayer();

		if ((!game()->player()->alive()) || (Time > LimitTime)) {
			game()->setGameTime(Time);
			game()->scene(GAME::SCENE_ID_GAME_OVER)->init();
			game()->changeScene(GAME::SCENE_ID_GAME_OVER);
		}
		else if (game()->enemiesManager()->aliveNum() == 0) {
			game()->setGameTime(Time);
			game()->scene(GAME::SCENE_ID_GAME_CLEAR)->init();
			game()->changeScene(GAME::SCENE_ID_GAME_CLEAR);
		}
	}
	void STAGE::draw() {
		//clear(); //�������SCENE::proc()�ł��Bupdate()���ł�print()�p�B
		rectMode(CENTER);
		game()->player()->draw();
		game()->enemiesManager()->draw();
		game()->playerBulletsManager()->draw();
		game()->enemiesBulletsManager()->draw();
		game()->block()->draw();

		//game()->playerBulletsManager()->DEBUG_notAliveCnt(); //���@�̎c�e�\���p(30�����炢�]���Ă�)
		//game()->enemiesBulletsManager()->DEBUG_notAliveCnt(); //�G�̎c�e�\���p(4�̎���30�����炢�]���Ă�)

		textSize(58);
		fill(255, 255, 0);
		char buf[128];
		sprintf_s(buf, sizeof(buf), "TIME:%05.2f/%dsec", Time, LimitTime);
		text(buf, 1100, 100.0f);

		textSize(60);
		float baseX = 450.0f;
		float baseY = 100.0f;
		float offsetY = 50.0f;
		int cnt = 0;
		if (game()->gameMode() == GAME::GAME_MODE_NORMAL) {
			fill(0);
			text("���E", 126, 83);
			fill(0,255,255);
			text("���E", 123, 80);
			fill(255);
			text("W,S�L�[: �㉺�Ɉړ�", baseX, baseY + offsetY * cnt++);
		}
		else if (game()->gameMode() == GAME::GAME_MODE_HARD) {
			fill(0, 255, 255);
			text("���E", 130, 95);
			fill(255);
			text("SPACE: �󒆒���p", baseX, baseY + offsetY * cnt++);
		}
		else if (game()->gameMode() == GAME::GAME_MODE_VERY_HARD) {
			fill(0, 255, 255);
			text("��E", 100, 95);
			fill(255);
			text("SPACE: �󒆒���p", baseX, baseY + offsetY * cnt++);
		}
	}
}
