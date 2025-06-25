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
        bool JumpedFlag = false; //1��ł��W�����v������true
        float JumpHight = 0; //���݈ʒu����㏸���鋗��
        float JumpAscentTime = 0; //���ݎ��Ԃ���㏸�������鎞��
        int JumpingCount = 0;
        float JumpedPosY = 0;
        float JumpingTime = 0;
        float GameOverMoveSpeed = 0; //�Q�[���I�[�o�[���̗������x
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
