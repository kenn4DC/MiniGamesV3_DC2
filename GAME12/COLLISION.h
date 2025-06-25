#pragma once

#include "GAME_OBJECT.h"

namespace GAME12 {

    class COLLISION :
        public GAME_OBJECT
    {
    private:
        int SndPlayerBulletVSEnemy = 0;
        int SndEnemyBulletVSPlayer = 0;
    public:
        COLLISION(class GAME* game);
        ~COLLISION();
        void create();
        bool CheckCollision_CircleAABB( //�~�Ƌ�`(���])�̓����蔻��
            float cx, float cy,   // �~�̒��S
            float cr,             // �~�̔��a
            float rx, float ry,   // ��`�̒��S���W
            float rw, float rh    // ��`�̕��ƍ���
        );
        bool CheckCollision(class CHARACTER* charaLH, class CHARACTER* charaRH);
        void playerBulletsVsEnemies();
        void enemiesBulletsVsPlayer();
    };

}
