#pragma once
#include "GAME_OBJECT.h"
#include "FLOAT2.h"

namespace GAME12 {

    class CHARACTER :
        public GAME_OBJECT
    {
    public:
        enum CHARACTER_SHAPE { //�L�����N�^�[�`��(�����蔻��p)
            CS_NON, //�Y���Ȃ�(�����蔻��ΏۊO)
            CS_CIRCLE, //�~
            CS_AABB, //���]��` ��Axis-Aligned Bounding Box
            CS_OBB, //��]��` ��Oriented Bounding Box
        };
    protected:
        int Img = 0;
        enum CHARACTER_SHAPE Shape = CS_NON;
        float ImgRadius = 0; //�摜�̒��S����̑傫��(���a)
        float ImgWidth = 0; //�摜�̕�
        float ImgHeight = 0; //�摜�̍���
        float BcRadius = 0; //�摜�̒��S����̋��E�~�̑傫��(���a) ��bounding circle radius.
        float BbWidth = 0; //�摜�̒��S����̕� ��bounding box width.
        float BbHeight = 0; //�摜�̒��S����̍��� ��boundig box height.
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
        bool BoundingBoxFlag = false; //�����蔻�肪�����Ȃ�
#else
        bool BoundingBoxFlag = true; //�����蔻�肪������(�ʗL������PLAYER,ENEMY_BULLET_MANAGER���ōs��)
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

