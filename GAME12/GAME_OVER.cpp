#include "../../libOne/inc/libOne.h"
#include "ENEMIES_MANAGER.h"
#include "ENEMIES_BULLETS_MANAGER.h"
#include "PLAYER.h"
#include "PLAYER_BULLETS_MANAGER.h"
#include "GAME12.h"
#include "GAME_OVER.h"

namespace GAME12 {

	GAME_OVER::GAME_OVER(class GAME* game) : SCENE(game) {
	}
	GAME_OVER::~GAME_OVER() {
	}
	void GAME_OVER::init() {
		Time = 0;
		NextScene = false;
		game()->player()->gameOverInit();
	}
	void GAME_OVER::update() {
		game()->player()->gameOverUpdate();
		game()->enemiesManager()->update();
		game()->playerBulletsManager()->update();
		game()->enemiesBulletsManager()->update();

		if (!game()->player()->alive()) {
			Time += delta;
			NextScene = true;
		}
	}
	void GAME_OVER::draw() {
		game()->player()->draw();
		game()->enemiesManager()->draw();
		game()->playerBulletsManager()->draw();
		game()->enemiesBulletsManager()->draw();

		if (NextScene) {
			textSize(150);
			fill(255, 255, 0);
			text("ゲームオーバー!!", 300, height / 2.0f + 75.0f);

			textSize(80);
			fill(255);
			text("N: リトライ", 600, height - 180.0f);
			text("B: タイトルに戻る", 600, height - 100.0f);
		}
	}
	void GAME_OVER::nextScene() {
		if (NextScene) {
			if (isTrigger(KEY_N)) {
				game()->scene(GAME::SCENE_ID_STAGE)->init();
				game()->changeScene(GAME::SCENE_ID_STAGE);
			}
			else if (isTrigger(KEY_B) || Time > 60.0f) {
				game()->scene(GAME::SCENE_ID_TITLE)->init();
				game()->changeScene(GAME::SCENE_ID_TITLE);
			}
		}
	}

}