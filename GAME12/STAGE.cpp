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
			LimitTime = 60; //20秒未満で行ける
		}
		else if (game()->gameMode() == GAME::GAME_MODE_HARD) {
			LimitTime = 50; //20秒未満で行ける
		}
		else if (game()->gameMode() == GAME::GAME_MODE_VERY_HARD) {
			LimitTime = 40; //1位:25.76秒, 2位:29.29秒, 3位:30.62秒でクリア実績あり!!!
		}
		else {
			//★Logic error.
			__debugbreak();
		}
		Time = 0;

		game()->player()->init();
		game()->enemiesManager()->init();
		game()->playerBulletsManager()->init();
		game()->enemiesBulletsManager()->init();
	}
	void STAGE::update() {
		//★Tキーによるストップ処理(clear() & draw() は行う)
		if (isTrigger(KEY_T)) {
			DebugStop = !DebugStop;
		}
		if (DebugStop) {
			return;
		}
		//強制クリア
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
		//clear(); //※これはSCENE::proc()でやる。update()内でのprint()用。
		rectMode(CENTER);
		game()->player()->draw();
		game()->enemiesManager()->draw();
		game()->playerBulletsManager()->draw();
		game()->enemiesBulletsManager()->draw();
		game()->block()->draw();

		//game()->playerBulletsManager()->DEBUG_notAliveCnt(); //自機の残弾表示用(30発ぐらい余ってる)
		//game()->enemiesBulletsManager()->DEBUG_notAliveCnt(); //敵の残弾表示用(4体時で30発ぐらい余ってる)

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
			text("下忍", 126, 83);
			fill(0,255,255);
			text("下忍", 123, 80);
			fill(255);
			text("W,Sキー: 上下に移動", baseX, baseY + offsetY * cnt++);
		}
		else if (game()->gameMode() == GAME::GAME_MODE_HARD) {
			fill(0, 255, 255);
			text("中忍", 130, 95);
			fill(255);
			text("SPACE: 空中跳躍術", baseX, baseY + offsetY * cnt++);
		}
		else if (game()->gameMode() == GAME::GAME_MODE_VERY_HARD) {
			fill(0, 255, 255);
			text("上忍", 100, 95);
			fill(255);
			text("SPACE: 空中跳躍術", baseX, baseY + offsetY * cnt++);
		}
	}
}
