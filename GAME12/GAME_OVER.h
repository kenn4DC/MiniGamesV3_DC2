#pragma once
#include "SCENE.h"
namespace GAME12 {
    class GAME_OVER :
        public SCENE
    {
    private:
        float Time = 0;
        bool NextScene = false;
    public:
        GAME_OVER(class GAME* game);
        ~GAME_OVER();
        void init();
        void update();
        void draw();
        void nextScene();
    };
}
