#pragma once
#include "SCENE.h"
namespace GAME12 {
    class TITLE :
        public SCENE
    {
    private:
        bool BlinkDraw = false;
        float BlinkInterval = 0;
        float BlinkTime = 0;
    public:
        TITLE(class GAME* game);
        ~TITLE();
        void init();
        void update();
        void draw();
        void nextScene();
    };
}

