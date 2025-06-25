#pragma once
#include "GAME_OBJECT.h"

namespace GAME12 {

    class BULLETS_MANAGER :
        public GAME_OBJECT
    {
    protected:
        int TotalNum = 0; //****_BULLET_MANAGERìôÇ≈å¬ï Ç…ê›íËÇ≥ÇÍÇÈ
        class BULLET** Bullets = nullptr;
    public:
        BULLETS_MANAGER(class GAME* game);
        virtual ~BULLETS_MANAGER();
        virtual void create() = 0;
        virtual void init();
        virtual void launch(const class FLOAT2& pos, const class FLOAT2& vec, float speed, float angSpeed) = 0;
        virtual void update();
        virtual void draw();
        virtual int totalNum();
        virtual class BULLET* bullet(int idx);
        virtual void DEBUG_notAliveCnt();
    };

}
