#pragma once
#include "SCENE.h"
namespace GAME12 {
    class STAGE :
        public SCENE
    {
    private:
        bool DebugStop = false;
        int LimitTime = 0;
        float Time = 0;
    public:
        STAGE(class GAME* game);
        ~STAGE();
        void init();
        void update();
        void draw();
    };
}

