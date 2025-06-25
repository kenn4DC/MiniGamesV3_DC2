#pragma once
#include "GAME_OBJECT.h"

namespace GAME12 {

    class ENEMIES_MANAGER :
        public GAME_OBJECT
    {
    private:
        int TotalNum = 0;
        int Img = 0;
        class ENEMY** Enemies = nullptr;
    public:
        ENEMIES_MANAGER(class GAME* game);
        ~ENEMIES_MANAGER();
        void create();
        void init();
        void update();
        void draw();
        int totalNum();
        class ENEMY* enemy(int idx);
        int aliveNum();
    };

}
