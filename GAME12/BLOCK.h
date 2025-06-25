#pragma once
#include "GAME_OBJECT.h"
namespace GAME12 {

    class BLOCK :
        public GAME_OBJECT
    {
    private:
        int Img = 0;
        float ImgWidth = 0;
        float ImgHeight = 0;
    public:
        BLOCK(class GAME* game);
        ~BLOCK();
        void create();
        void draw();
    };

}

