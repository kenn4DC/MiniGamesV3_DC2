#include "../../libOne/inc/libOne.h"
#include "PLAYER.h"
#include "GAME12.h"
#include "BLOCK.h"

namespace GAME12 {

	BLOCK::BLOCK(class GAME* game) : GAME_OBJECT(game) {}
	BLOCK::~BLOCK(){}
	void BLOCK::create() {
		Img = loadImage("../MAIN/assets/game12/block.png");
		ImgWidth = 200.0f;
		ImgHeight = 100.0f;
	}
	void BLOCK::draw() {
		if (game()->gameMode() == GAME::GAME_MODE_NORMAL) {
			image(Img, 100 + ImgWidth / 2.0f, 0 + ImgHeight / 2.0f); //“Vˆä
			image(Img, 100 + ImgWidth / 2.0f, height - ImgHeight / 2.0f); //°
		}
		else if (game()->gameMode() == GAME::GAME_MODE_HARD) {
			image(Img, 100 + ImgWidth / 2.0f, height - ImgHeight / 2.0f); //°
		}
		else if (game()->gameMode() == GAME::GAME_MODE_VERY_HARD) {
			if (!game()->player()->jumpedFlag()) { //‰‰ñƒWƒƒƒ“ƒv‚ª‚Ü‚¾‚È‚ç•`‰æ
				image(Img, 100 + ImgWidth / 2.0f, height - ImgHeight / 2.0f); //°
			}
		}
	}
}

