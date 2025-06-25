#pragma once
#include "GAME_OBJECT.h"
#include "FLOAT2.h"

namespace GAME12 {

    class CHARACTER :
        public GAME_OBJECT
    {
    public:
        enum CHARACTER_SHAPE { //キャラクター形状(当たり判定用)
            CS_NON, //該当なし(当たり判定対象外)
            CS_CIRCLE, //円
            CS_AABB, //非回転矩形 ※Axis-Aligned Bounding Box
            CS_OBB, //回転矩形 ※Oriented Bounding Box
        };
    protected:
        int Img = 0;
        enum CHARACTER_SHAPE Shape = CS_NON;
        float ImgRadius = 0; //画像の中心からの大きさ(半径)
        float ImgWidth = 0; //画像の幅
        float ImgHeight = 0; //画像の高さ
        float BcRadius = 0; //画像の中心からの境界円の大きさ(半径) ※bounding circle radius.
        float BbWidth = 0; //画像の中心からの幅 ※bounding box width.
        float BbHeight = 0; //画像の中心からの高さ ※boundig box height.
        float Scale = 0;
        FLOAT2 Pos;
        FLOAT2 Vec;
        float Speed = 0;
        float Angle = 0;
        float AngSpeed = 0;
        int MaxHp = 0;
        int Hp = 0;
        bool Alive = false;
#if 1
        bool BoundingBoxFlag = false; //当たり判定が見えない
#else
        bool BoundingBoxFlag = true; //当たり判定が見える(個別有効化はPLAYER,ENEMY_BULLET_MANAGER等で行う)
#endif
    public:
        CHARACTER(class GAME* game);
        virtual ~CHARACTER();
        virtual void setImg(int img);
        virtual void setImgWidth(float imgWidth);
        virtual void setImgHeight(float imgHeight);
        virtual FLOAT2 pos();
        virtual void setShape(CHARACTER_SHAPE shape);
        virtual enum CHARACTER_SHAPE shape();
        virtual void setBcRadius(float bcRadisu);
        virtual float bcRadius();
        virtual void setBbWidth(float bbWidth);
        virtual float bbWidth();
        virtual void setBbHeight(float bbHeight);
        virtual float bbHeight();
        virtual void setScale(float sclae);
        virtual float scale();
        virtual void draw();
        virtual void setAlive(bool alive);
        virtual bool alive();
        virtual void setMaxHp(int maxHp);
        virtual int maxHp();
        virtual void setHp(int hp);
        virtual int hp();
        virtual void setBoundingBoxFlag(bool boundingBoxFlag);
    };

}

