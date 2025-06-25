#pragma once
#include "BULLETS_MANAGER.h"

namespace GAME12 {
    class PLAYER_BULLETS_MANAGER :
        public BULLETS_MANAGER
    {
    public:
        PLAYER_BULLETS_MANAGER(class GAME* game);
        void create();
        void launch(const class FLOAT2& pos, const class FLOAT2& vec, float speed, float angSpeed);
    };

}


