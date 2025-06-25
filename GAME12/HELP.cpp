#include "../../libOne/inc/libOne.h"
#include "GAME12.h"
#include "HELP.h"

namespace GAME12 {

	HELP::HELP(class GAME* game) : SCENE(game) {
		Imgs = new int[PageNum];
	}
	HELP::~HELP() {
		delete[] Imgs;
	}
	void HELP::create() {
		Imgs[0] = loadImage("../MAIN/assets/game12/HELP1.png");
		Imgs[1] = loadImage("../MAIN/assets/game12/HELP2.png");
		Imgs[2] = loadImage("../MAIN/assets/game12/HELP3.png");
		Imgs[3] = loadImage("../MAIN/assets/game12/HELP4.png");
	}
	void HELP::init() {
		Page = 0;
	}
	void HELP::draw() {
		rectMode(CORNER);
		image(Imgs[Page], 0, 0);

		textSize(50);
		fill(255);
		text((let)(Page + 1) + "／" + (let)4 + "頁", 800, height - 100);

		textSize(50);
		fill(255);
		if (Page < PageNum - 1) {
			text("    N: 次ページ", 1200, height - 100.0f);
		}
		else {
			text("    N: タイトルに戻る", 1200, height - 100.0f);
		}
	}
	void HELP::nextScene() {
		if (isTrigger(KEY_N)) {
			Page++;
			if (Page >= PageNum) {
				game()->scene(GAME::SCENE_ID_TITLE)->init();
				game()->changeScene(GAME::SCENE_ID_TITLE);
			}
		}
	}

}
