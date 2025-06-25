#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "SCENE.h"
#include "TITLE.h"
#include "HELP.h"
#include "STAGE.h"
#include "GAME_CLEAR.h"
#include "GAME_OVER.h"
#include "PLAYER.h"
#include "ENEMIES_MANAGER.h"
#include "PLAYER_BULLETS_MANAGER.h"
#include "ENEMIES_BULLETS_MANAGER.h"
#include "BLOCK.h"
#include "COLLISION.h"
#include "GAME12.h"
namespace GAME12
{
	int GAME::create()
	{
		//game common
		hideCursor();
		angleMode(RADIANS);

		//new etc.
		//※必要なリソースは起動直後に確保し終了直前までキープさせる方針でいく
		//  STAGEシーンで飛んでいた弾をGAME_OVERシーンで画面外消滅まで引き継ぐとかできる
		Scenes[SCENE_ID_TITLE] = new TITLE(this);
		Scenes[SCENE_ID_HELP] = new HELP(this);
		Scenes[SCENE_ID_STAGE] = new STAGE(this);
		Scenes[SCENE_ID_GAME_CLEAR] = new GAME_CLEAR(this);
		Scenes[SCENE_ID_GAME_OVER] = new GAME_OVER(this);
		//CurSceneId = TITLE_ID; //メンバ変数のコピー初期化したので不要
		//※STAGEシーン等で必要になるキャラクターなど
		//  MANAGERクラスは複数体のキャラクターの管理クラス
		Player = new PLAYER(this);
		EnemiesManager = new ENEMIES_MANAGER(this); //各ENEMYのオブジェクトの作成を内部で行っている
		PlayerBulletsManager = new PLAYER_BULLETS_MANAGER(this); //各PLAYER_BULLETのオブジェクトの作成を内部で行っている
		EnemiesBulletsManager = new ENEMIES_BULLETS_MANAGER(this); //各ENEMY_BULLETのオブジェクトの作成を内部で行っている
		Block = new BLOCK(this);
		Collision = new COLLISION(this);

		//loadImage(), loadSound() etc.
		//※画像や音楽はゲームリトライ時等でも変わらないのでここで事前に設定
		Scenes[SCENE_ID_HELP]->create(); //Imgの設定を内部で行っている
		Player->create(); //Imgの設定を内部で行っている
		EnemiesManager->create(); //各ENEMYのImgの設定を内部で行っている
		PlayerBulletsManager->create(); //各BULLETのImgの設定を内部で行っている
		EnemiesBulletsManager->create(); //各BULLETのImgの設定を内部で行っている
		Block->create(); //Imgの設定を内部で行っている

		SndBGMs[SOUND_BGM_NORMAL] = loadSound("../MAIN/assets/game12/SndLevelNormalBGM.wav");
		SndBGMs[SOUND_BGM_HARD] = loadSound("../MAIN/assets/game12/SndLevelHardBGM.wav");
		SndBGMs[SOUND_BGM_VERY_HARD] = loadSound("../MAIN/assets/game12/SndLevelVeryHardBGM.wav");
		SndBGMs[SOUND_BGM_GAME_CLEAR] = loadSound("../MAIN/assets/game12/SndGameClearBGM.wav");
		Collision->create(); //衝突時のSnd***の設定を行っている

		SndBGMStart = false;
		Scenes[GAME::SCENE_ID_TITLE]->init();
		changeScene(GAME::SCENE_ID_TITLE);
		return 0;
	}

	void GAME::destroy()
	{
		delete Collision;
		delete Block;
		delete EnemiesBulletsManager; //各ENEMY_BULLETの解放は内部で行っている
		delete PlayerBulletsManager; //各PLAYER_BULLETの解放は内部で行っている
		delete EnemiesManager; //各ENEMYの解放は内部で行っている
		delete Player;
		for (int i = 0; i < SCENE_ID_NUM; i++) {
			delete Scenes[i];
		}

		//出来るだけ最初の状態へ戻しておく
		if (SndBGMStart) {
			stopSound(SndNowBGM);
		}
		angleMode(DEGREES);
		showCursor();
	}

	void GAME::proc()
	{
		Scenes[CurSceneId]->proc();

		if (isTrigger(KEY_ENTER)) {
			main()->backToMenu();
		}
	}

	void GAME::changeScene(SCENE_ID sceneId) {
		CurSceneId = sceneId;
	}
}
