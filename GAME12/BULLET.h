#pragma once
#include "CHARACTER.h"

namespace GAME12 {

    class BULLET :
        public CHARACTER
    {
    public:
        BULLET(class GAME* game);
        virtual ~BULLET();
        virtual void init();
        virtual void update();
        virtual void launch(const class FLOAT2& pos, const class FLOAT2& vec, float speed, float angSpeed);
        virtual void damage();
    };

}
