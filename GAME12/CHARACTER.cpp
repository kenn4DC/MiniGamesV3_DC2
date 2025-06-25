#include "../../libOne/inc/libOne.h"
#include "CHARACTER.h"

namespace GAME12 {

    CHARACTER::CHARACTER(class GAME* game) : GAME_OBJECT(game) {
	}
	CHARACTER::~CHARACTER() {
	}
    void CHARACTER::setImg(int img) {
        Img = img;
    }
    void CHARACTER::setImgWidth(float imgWidth) {
        ImgWidth = imgWidth;
    }
    void CHARACTER::setImgHeight(float imgHeight) {
        ImgHeight = imgHeight;
    }
    FLOAT2 CHARACTER::pos() {
        return Pos;
    }
    void CHARACTER::setShape(CHARACTER_SHAPE shape) {
        Shape = shape;
    }
    enum CHARACTER::CHARACTER_SHAPE CHARACTER::shape() {
        return Shape;
    }
    void CHARACTER::setBcRadius(float bcRadisu) {
        BcRadius = bcRadisu;
    }
    float CHARACTER::bcRadius() {
        return BcRadius;
    }
    void CHARACTER::setBbWidth(float bbWidth) {
        BbWidth = bbWidth;
    }
    float CHARACTER::bbWidth() {
        return BbWidth;
    }
    void CHARACTER::setBbHeight(float bbHeight) {
        BbHeight = bbHeight;
    }
    float CHARACTER::bbHeight() {
        return BbHeight;
    }
    void CHARACTER::draw() {
        if (Alive) {
            fill(0, 0, 0, 128);
            image(Img, Pos.x, Pos.y, Angle, Scale);
            if (BoundingBoxFlag) {
                fill(128, 0, 0, 128);
                strokeWeight(0.0f);
                if (Shape == CS_CIRCLE) {
                    circle(Pos.x, Pos.y, BcRadius * Scale * 2.0f);
                }
                else if (Shape == CS_AABB){
                    rect(Pos.x, Pos.y, BbWidth * Scale, BbHeight * Scale);
                }
                else if (Shape == CS_OBB) {
                    //ÅöYet
                    __debugbreak();
                }
                else if (Shape == CS_NON) {
                    ;
                }
            }
        }
    }
    void CHARACTER::setScale(float scale) {
        Scale = scale;
    }
    float CHARACTER::scale() {
        return Scale;
    }
    void CHARACTER::setAlive(bool alive) {
        Alive = alive;
    }
    bool CHARACTER::alive() {
        return Alive;
    }
    void CHARACTER::setMaxHp(int maxHp) {
        MaxHp = maxHp;
    }
    int CHARACTER::maxHp() {
        return MaxHp;
    }
    void CHARACTER::setHp(int hp) {
        Hp = hp;
    }
    int CHARACTER::hp() {
        return Hp;
    }
    void CHARACTER::setBoundingBoxFlag(bool boundingBoxFlag) {
        BoundingBoxFlag = boundingBoxFlag;
    }

}
