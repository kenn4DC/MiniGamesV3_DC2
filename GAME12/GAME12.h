#pragma once
#include "../MAIN/GAME_BASE.h"
namespace GAME12
{
    class GAME :
        public GAME_BASE
    {
    //シーン
    public:
        enum SCENE_ID {
            SCENE_ID_TITLE,
            SCENE_ID_HELP,
            SCENE_ID_STAGE,
            SCENE_ID_GAME_CLEAR,
            SCENE_ID_GAME_OVER,
            SCENE_ID_NUM
        };
        enum GAME_MODE {
            GAME_MODE_NORMAL,
            GAME_MODE_HARD,
            GAME_MODE_VERY_HARD,
            GAME_MODE_NUM
        };
        enum SOUND_BGM {
            SOUND_BGM_NORMAL,
            SOUND_BGM_HARD,
            SOUND_BGM_VERY_HARD,
            SOUND_BGM_GAME_CLEAR,
            SOUND_BGM_NUM
        };
    private:
        class SCENE* Scenes[SCENE_ID_NUM]{};
        SCENE_ID CurSceneId = SCENE_ID_TITLE;
    //キャラクター
    private:
        class PLAYER* Player = nullptr;
        class ENEMIES_MANAGER* EnemiesManager = nullptr;
        class BULLETS_MANAGER* PlayerBulletsManager = nullptr;
        class BULLETS_MANAGER* EnemiesBulletsManager = nullptr;
        class BLOCK* Block = nullptr;
        class COLLISION* Collision = nullptr;
    public:
        class SCENE* scene(SCENE_ID sceneId) { return Scenes[sceneId]; }
        class PLAYER* player() { return Player; }
        class ENEMIES_MANAGER* enemiesManager() { return EnemiesManager; }
        class BULLETS_MANAGER* playerBulletsManager() { return PlayerBulletsManager; }
        class BULLETS_MANAGER* enemiesBulletsManager() { return EnemiesBulletsManager; }
        class BLOCK* block() { return Block; }
        class COLLISION* collision() { return Collision; }
        //ゲーム
    private:
        enum GAME_MODE GameMode = GAME_MODE_NORMAL;
        float GameTime = 0;
        bool SndBGMStart = false;
        int SndNowBGM = 0;
        int SndBGMs[4]{};
    public:
        GAME(class MAIN* main) : GAME_BASE(main) {}
        ~GAME(){}
        int create();
        void proc();
        void destroy();
        void changeScene(SCENE_ID sceneId);
        SCENE* curScene() { return Scenes[CurSceneId]; }
        void setSndBGMStart(bool flg) { SndBGMStart = flg; }
        bool sndBGMStart() { return SndBGMStart; }
        void setSndNowBGM(int snd) { SndNowBGM = snd; }
        int sndNowBGM() { return SndNowBGM; }
        int sndBGMs(int idx) { return SndBGMs[idx]; }
        void setGameMode(enum GAME_MODE gameMode) { GameMode = gameMode; }
        enum GAME_MODE gameMode() { return GameMode; }
        void setGameTime(float gameTime) { GameTime = gameTime; }
        float gameTime() { return GameTime; }
    };

}
