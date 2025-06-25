#include "../../libOne/inc/libOne.h"
#include "GAME_OBJECT.h"
#include "BULLET.h"
#include "BULLETS_MANAGER.h"

namespace GAME12 {

	BULLETS_MANAGER::BULLETS_MANAGER(class GAME* game) : GAME_OBJECT(game) {
	}
	BULLETS_MANAGER::~BULLETS_MANAGER() {
		for (int i = 0; i < TotalNum; i++) {
			if (Bullets[i]) {
				delete Bullets[i];
				Bullets[i] = nullptr;
			}
		}
		if (Bullets) {
			delete[] Bullets;
			Bullets = nullptr;
		}
	}
	//void BULLET_MANAGER::create() {
	//}
	void BULLETS_MANAGER::init(){
		for (int i = 0; i < TotalNum; i++) {
			bullet(i)->init(); //Alive change false.
		}
	}
	//void BULLET_MANAGER::launch(const FLOAT2& pos, const FLOAT2& vec, float speed, float angSpeed) {
	//}
	void BULLETS_MANAGER::update(){
		for (int i = 0; i < TotalNum; i++) {
			bullet(i)->update();
		}
	}
	void BULLETS_MANAGER::draw(){
		for (int i = 0; i < TotalNum; i++) {
			bullet(i)->draw();
		}
	}
	void BULLETS_MANAGER::DEBUG_notAliveCnt() {
		int notAliveCnt = 0;
		for (int i = 0; i < TotalNum; i++) {
			if (!bullet(i)->alive()) {
				notAliveCnt++;
			}
		}
		printSize(50);
		fill(255);
		print((let)"notAliveCnt=" + notAliveCnt);
	}
	int BULLETS_MANAGER::totalNum() {
		return TotalNum;
	}
	BULLET* BULLETS_MANAGER::bullet(int idx) {
		return Bullets[idx];
	}

}