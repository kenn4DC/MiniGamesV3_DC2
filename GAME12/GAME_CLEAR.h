#pragma once
#include "SCENE.h"
namespace GAME12 {
    class GAME_CLEAR :
        public SCENE
    {
    private:
        float Time = 0;
        bool BlinkDraw = false;
        float BlinkInterval = 0;
        bool NextScene = false;
    public:
        GAME_CLEAR(class GAME* game);
        ~GAME_CLEAR();
        void init();
        void update();
        void draw();
        void nextScene();
    };
}
