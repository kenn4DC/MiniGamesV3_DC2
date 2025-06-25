#pragma once
#include "SCENE.h"
namespace GAME12 {
    class HELP :
        public SCENE
    {
    private:
        int* Imgs = nullptr;
        const int PageNum = 4;
        int Page = 0;
    public:
        HELP(class GAME* game);
        ~HELP();
        void create();
        void init();
        void draw();
        void nextScene();
    };

}
