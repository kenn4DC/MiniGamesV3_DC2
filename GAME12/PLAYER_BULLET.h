#pragma once
#include "BULLET.h"

namespace GAME12 {

    class PLAYER_BULLET :
        public BULLET
    {
    public:
        PLAYER_BULLET(class GAME* game);
        ~PLAYER_BULLET();
    };

}

