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
		//���K�v�ȃ��\�[�X�͋N������Ɋm�ۂ��I�����O�܂ŃL�[�v��������j�ł���
		//  STAGE�V�[���Ŕ��ł����e��GAME_OVER�V�[���ŉ�ʊO���ł܂ň����p���Ƃ��ł���
		Scenes[SCENE_ID_TITLE] = new TITLE(this);
		Scenes[SCENE_ID_HELP] = new HELP(this);
		Scenes[SCENE_ID_STAGE] = new STAGE(this);
		Scenes[SCENE_ID_GAME_CLEAR] = new GAME_CLEAR(this);
		Scenes[SCENE_ID_GAME_OVER] = new GAME_OVER(this);
		//CurSceneId = TITLE_ID; //�����o�ϐ��̃R�s�[�����������̂ŕs�v
		//��STAGE�V�[�����ŕK�v�ɂȂ�L�����N�^�[�Ȃ�
		//  MANAGER�N���X�͕����̂̃L�����N�^�[�̊Ǘ��N���X
		Player = new PLAYER(this);
		EnemiesManager = new ENEMIES_MANAGER(this); //�eENEMY�̃I�u�W�F�N�g�̍쐬������ōs���Ă���
		PlayerBulletsManager = new PLAYER_BULLETS_MANAGER(this); //�ePLAYER_BULLET�̃I�u�W�F�N�g�̍쐬������ōs���Ă���
		EnemiesBulletsManager = new ENEMIES_BULLETS_MANAGER(this); //�eENEMY_BULLET�̃I�u�W�F�N�g�̍쐬������ōs���Ă���
		Block = new BLOCK(this);
		Collision = new COLLISION(this);

		//loadImage(), loadSound() etc.
		//���摜�≹�y�̓Q�[�����g���C�����ł��ς��Ȃ��̂ł����Ŏ��O�ɐݒ�
		Scenes[SCENE_ID_HELP]->create(); //Img�̐ݒ������ōs���Ă���
		Player->create(); //Img�̐ݒ������ōs���Ă���
		EnemiesManager->create(); //�eENEMY��Img�̐ݒ������ōs���Ă���
		PlayerBulletsManager->create(); //�eBULLET��Img�̐ݒ������ōs���Ă���
		EnemiesBulletsManager->create(); //�eBULLET��Img�̐ݒ������ōs���Ă���
		Block->create(); //Img�̐ݒ������ōs���Ă���

		SndBGMs[SOUND_BGM_NORMAL] = loadSound("../MAIN/assets/game12/SndLevelNormalBGM.wav");
		SndBGMs[SOUND_BGM_HARD] = loadSound("../MAIN/assets/game12/SndLevelHardBGM.wav");
		SndBGMs[SOUND_BGM_VERY_HARD] = loadSound("../MAIN/assets/game12/SndLevelVeryHardBGM.wav");
		SndBGMs[SOUND_BGM_GAME_CLEAR] = loadSound("../MAIN/assets/game12/SndGameClearBGM.wav");
		Collision->create(); //�Փˎ���Snd***�̐ݒ���s���Ă���

		SndBGMStart = false;
		Scenes[GAME::SCENE_ID_TITLE]->init();
		changeScene(GAME::SCENE_ID_TITLE);
		return 0;
	}

	void GAME::destroy()
	{
		delete Collision;
		delete Block;
		delete EnemiesBulletsManager; //�eENEMY_BULLET�̉���͓����ōs���Ă���
		delete PlayerBulletsManager; //�ePLAYER_BULLET�̉���͓����ōs���Ă���
		delete EnemiesManager; //�eENEMY�̉���͓����ōs���Ă���
		delete Player;
		for (int i = 0; i < SCENE_ID_NUM; i++) {
			delete Scenes[i];
		}

		//�o���邾���ŏ��̏�Ԃ֖߂��Ă���
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
