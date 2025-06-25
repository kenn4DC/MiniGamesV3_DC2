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
        bool CheckCollision_CircleAABB( //円と矩形(非回転)の当たり判定
            float cx, float cy,   // 円の中心
            float cr,             // 円の半径
            float rx, float ry,   // 矩形の中心座標
            float rw, float rh    // 矩形の幅と高さ
        );
        bool CheckCollision(class CHARACTER* charaLH, class CHARACTER* charaRH);
        void playerBulletsVsEnemies();
        void enemiesBulletsVsPlayer();
    };

}
