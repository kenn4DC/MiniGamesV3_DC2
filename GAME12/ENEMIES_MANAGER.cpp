#include "../../libOne/inc/libOne.h"
#include "ENEMY.h"
#include "ENEMIES_MANAGER.h"

namespace GAME12 {

	ENEMIES_MANAGER::ENEMIES_MANAGER(class GAME* game) : GAME_OBJECT(game) {
	}
	ENEMIES_MANAGER::~ENEMIES_MANAGER() {
		if (Enemies) {
			for (int i = 0; i < TotalNum; i++) {
				if (Enemies[i]) {
					delete Enemies[i];
					Enemies[i] = nullptr;
				}
			}
			delete[] Enemies;
			Enemies = nullptr;
		}
	}
	void ENEMIES_MANAGER::create(){
		TotalNum = 2;
		Enemies = new ENEMY*[TotalNum] {}; //ENEMYのコンストラクタは引数付きなので別にnewする

		for (int i = 0; i < TotalNum; i++) {
			Enemies[i] = new ENEMY(game()); //この後から enemy(i) は使える
		}

		Img = loadImage("../MAIN/assets/game12/enemy.png");
		for (int i = 0; i < TotalNum; i++) {
			enemy(i)->setShape(CHARACTER::CS_AABB);
			enemy(i)->setImg(Img);
			enemy(i)->setImgWidth(196.0f);
			enemy(i)->setImgHeight(209.0f);
			enemy(i)->setBbWidth(172);
			enemy(i)->setBbHeight(186);
			//enemy(i)->setBoundingBoxFlag(true);
		}
	}
	void ENEMIES_MANAGER::init(){
		for (int i = 0; i < TotalNum; i++) {
			float px = width - 200.0f;
			float offset = height / TotalNum;
			float top = offset / 2.0f;
			float py = top + offset * i;
			enemy(i)->init(px, py);
			enemy(i)->setCenterPosY(py);
		}
	}
	void ENEMIES_MANAGER::update(){
		for (int i = 0; i < TotalNum; i++) {
			enemy(i)->update();
		}
	}
	void ENEMIES_MANAGER::draw(){
		for (int i = 0; i < TotalNum; i++) {
			enemy(i)->draw();
		}
	}
	int ENEMIES_MANAGER::totalNum() {
		return TotalNum;
	}
	class ENEMY* ENEMIES_MANAGER::enemy(int idx) {
		return Enemies[idx];
	}
	int ENEMIES_MANAGER::aliveNum() {
		int cnt = 0;
		for (int i = 0; i < TotalNum; i++) {
			if (enemy(i)->alive()) {
				cnt++;
			}
		}
		return cnt;
	}
}