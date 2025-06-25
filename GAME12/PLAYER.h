#pragma once
#include "CHARACTER.h"

namespace GAME12 {

    class PLAYER :
        public CHARACTER
    {
    private:
        float BulletLaunchInterval = 0;
        float BulletLaunchRestTime = 0;
        float BulletSpeed = 0;
        float BulletAngSpeed = 0;
        bool JumpedFlag = false; //1回でもジャンプしたらtrue
        float JumpHight = 0; //現在位置から上昇する距離
        float JumpAscentTime = 0; //現在時間から上昇し続ける時間
        int JumpingCount = 0;
        float JumpedPosY = 0;
        float JumpingTime = 0;
        float GameOverMoveSpeed = 0; //ゲームオーバー時の落下速度
        bool AutoLaunch = false;
    public:
        PLAYER(class GAME* game);
        ~PLAYER();
        void create();
        void init();
        void update();
        void move();
        void moveUpDown();
        void moveJump();
        void launch();
        void damage();
        bool jumpedFlag();
        void gameOverInit();
        void gameOverUpdate();
        void gameClearInit();
        void gameClearUpdate();
    };

}
