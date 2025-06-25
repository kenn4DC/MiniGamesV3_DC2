#include "../../libOne/inc/libOne.h"
#include "GAME12.h"
#include "TITLE.h"

namespace GAME12 {
    TITLE::TITLE(class GAME* game) : SCENE(game){
    }
    TITLE::~TITLE(){
    }
    void TITLE::init() {
        BlinkDraw = true;
        BlinkInterval = 0.4f;
        BlinkTime = 0.0f;
        if (!game()->sndBGMStart()) {
            //‰‰ñŽž‚ÍƒQ[ƒ€ƒ‚[ƒh‚Í•K‚¸NORMAL‚Æ‚È‚Á‚Ä‚¢‚é
            game()->setSndNowBGM(game()->sndBGMs(GAME::SOUND_BGM_NORMAL));
            playLoopSound(game()->sndNowBGM());
            game()->setSndBGMStart(true);
        }
    }
	void TITLE::update() {
		BlinkTime += delta;
		if ((int)(BlinkTime / BlinkInterval) % 2 == 0) {
			BlinkDraw = true;
		}
		else {
			BlinkDraw = false;
		}

		int prev = game()->gameMode();
		int mode = prev;
		if (isTrigger(KEY_A) || isTrigger(KEY_LEFT)) {
			mode--;
			if (mode < 0) {
                mode = 0;
            }
		}
		else if (isTrigger(KEY_D) || isTrigger(KEY_RIGHT)) {
			mode++;
            if (mode > GAME::GAME_MODE_NUM - 1) {
                mode = GAME::GAME_MODE_NUM - 1;
			}
		}
        game()->setGameMode((GAME::GAME_MODE)mode);
        if (prev != game()->gameMode()) {
            BlinkTime = 0;
            //BGM•ÏX
            if (game()->sndBGMStart()) {
                stopSound(game()->sndNowBGM());
                if (game()->gameMode() == GAME::GAME_MODE_NORMAL) {
                    game()->setSndNowBGM(game()->sndBGMs(GAME::SOUND_BGM_NORMAL));
                }
                else if (game()->gameMode() == GAME::GAME_MODE_HARD) {
                    game()->setSndNowBGM(game()->sndBGMs(GAME::SOUND_BGM_HARD));
                }
                else if (game()->gameMode() == GAME::GAME_MODE_VERY_HARD) {
                    game()->setSndNowBGM(game()->sndBGMs(GAME::SOUND_BGM_VERY_HARD));
                }
                playLoopSound(game()->sndNowBGM());
            }
		}
	}
    void TITLE::draw(){
        textSize(200);
        fill(255, 0, 255);
        text("`      `", 450, 350);
        textSize(250);
        text("”El", 700, 300);

        textSize(75);
        fill(255);
        text("‰º”E", 500, 450);
        text("’†”E", 900, 450);
        text("ã”E", 1300, 450);
        float asterX = 425;
        if (game()->gameMode() == GAME::GAME_MODE_NORMAL) {
            asterX += 0;
        }
        else if (game()->gameMode() == GAME::GAME_MODE_HARD) {
            asterX += 400;
        }
        else if (game()->gameMode() == GAME::GAME_MODE_VERY_HARD) {
            asterX += 800;
        }
        if (BlinkDraw) {
            fill(255, 0, 0);
            text("š", asterX, 450);
        }
        textSize(60);
        fill(255, 255, 0);
        text("© AƒL[  “ïˆÕ“x•ÏX  DƒL[ ¨", 500, 550);

        textSize(100);
        fill(0, 255, 255);
        float baseX = 400.0f;
        float baseY = height / 2.0f + 50.0f;
        float offset = 100.0f;
        if (game()->gameMode() == GAME::GAME_MODE_NORMAL) {
            text("”El‚ð‘€ì‚µUŒ‚‚ðç]‚µ", baseX, baseY + offset * 1);
            text("Žè— Œ•‚Å‘û’B‚ðŒ‚”j‚µ‚ë", baseX, baseY + offset * 2);
        }
        else if (game()->gameMode() == GAME::GAME_MODE_HARD) {
            text("”El‚ð’µ–ô‚³‚¹Žè— Œ•‚Å", baseX, baseY + offset * 1);
            text("‘û’B‚ðŒ‚”j‚µ‚ë", baseX, baseY + offset * 2);
        }
        else if (game()->gameMode() == GAME::GAME_MODE_VERY_HARD) {
            text("”El‚ð’µ–ô‚³‚¹‘±‚¯‚Ä", baseX, baseY + offset * 1);
            text("Žè— Œ•‚Å‘û’B‚ðŒ‚”j‚µ‚ë", baseX, baseY + offset * 2);
        }

        textSize(50);
        fill(255);
        text("    H: à–¾", 1200, height - 200.0f);
        text("    N: ƒXƒ^[ƒg", 1200, height - 150.0f);
        text("ENTER: ƒƒjƒ…[‚É–ß‚é", 1200, height - 100.0f);

        textSize(35);
        fill(255);
        text("Sound:OtoLogicƒtƒŠ[‘fÞŽg—p", 100, height - 100.0f);
    }
    void TITLE::nextScene(){
        if (isTrigger(KEY_N)) {
            game()->scene(GAME::SCENE_ID_STAGE)->init();
            game()->changeScene(GAME::SCENE_ID_STAGE);
        }
        else if (isTrigger(KEY_H)) {
            game()->scene(GAME::SCENE_ID_HELP)->init();
            game()->changeScene(GAME::SCENE_ID_HELP);
        }
    }
}