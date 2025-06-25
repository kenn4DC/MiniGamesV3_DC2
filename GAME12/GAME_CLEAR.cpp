#include "../../libOne/inc/libOne.h"
#include "PLAYER.h"
#include "GAME12.h"
#include "GAME_CLEAR.h"

namespace GAME12 {

	GAME_CLEAR::GAME_CLEAR(class GAME* game) : SCENE(game) {
	}
	GAME_CLEAR::~GAME_CLEAR() {
	}
	void GAME_CLEAR::init() {
		BlinkInterval = 0.4f;
		Time = 0.0f;
		NextScene = false;

		if (game()->gameMode() == GAME::GAME_MODE_VERY_HARD) {
			if (game()->sndBGMStart()) {
				stopSound(game()->sndNowBGM());
				game()->setSndNowBGM(game()->sndBGMs(GAME::SOUND_BGM_GAME_CLEAR));
				//playLoopSound(game()->sndNowBGM()); //�]�C�𖡂킢�����̂Ń��[�v�����Ȃ�
				playSound(game()->sndNowBGM());
			}
			game()->player()->gameClearInit();
		}
	}
	void GAME_CLEAR::update() {
		if (game()->gameMode() == GAME::GAME_MODE_VERY_HARD) {
			game()->player()->gameClearUpdate();
			FLOAT2 playerPos = game()->player()->pos();
			if (playerPos.x > width / 2.0f) {
				NextScene = true;
			}
		}

		Time += delta;
		if ((int)(Time / BlinkInterval) % 2 == 0) {
			BlinkDraw = true;
		}
		else {
			BlinkDraw = false;
		}
	}
	void GAME_CLEAR::draw() {
		if (game()->gameMode() == GAME::GAME_MODE_VERY_HARD) {
			game()->player()->draw();
		}

		if (BlinkDraw) {
			textSize(150);
			fill(255, 255, 0);
			text("�Q�[���N���A!!", 400, height / 2.0f + 75.0f);
		}

		textSize(75);
		fill(0, 255, 255);
		char buf[128];
		sprintf_s(buf, sizeof(buf), "%.2f", game()->gameTime());
		text((let)"�^�C���F" + buf + (let)"�b", 700, 800);

		textSize(80);
		fill(255);
		text("N: �^�C�g���ɖ߂�", 600, height - 100.0f);
	}
	void GAME_CLEAR::nextScene() {
		if (
			(isTrigger(KEY_N)) ||
			((game()->gameMode() != GAME::GAME_MODE_VERY_HARD) && Time > 60.0f) || //Normal, Hard��1���o�����狭���^�C�g��
			((game()->gameMode() == GAME::GAME_MODE_VERY_HARD) && Time > 90.0f) //VeryHard�̃N���A���y�̓t�F�[�h�A�E�g����ɖ߂�
		) { //5���o�����狭���^�C�g��
			if (game()->gameMode() == GAME::GAME_MODE_VERY_HARD) {
				if (game()->sndBGMStart()) {
					stopSound(game()->sndNowBGM());
					game()->setSndNowBGM(game()->sndBGMs(GAME::SOUND_BGM_VERY_HARD));
					playLoopSound(game()->sndNowBGM());
				}
			}
			game()->scene(GAME::SCENE_ID_TITLE)->init();
			game()->changeScene(GAME::SCENE_ID_TITLE);
		}
	}
}