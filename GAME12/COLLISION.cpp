#define NOMINMAX //<algorithim>や<Windows.h>でstd::max(), std::min()でエラーが出たのを回避するために必要 by ChatGPT
#include <algorithm>
#include "../../libOne/inc/libOne.h"
#include "CHARACTER.h"
#include "PLAYER.h"
#include "ENEMY.h"
#include "BULLET.h"
#include "BULLETS_MANAGER.h"
#include "ENEMIES_MANAGER.h"
#include "SCENE.h"
#include "GAME12.h"
#include "COLLISION.h"

namespace GAME12 {

	COLLISION::COLLISION(class GAME* game) : GAME_OBJECT(game){
	}
	COLLISION::~COLLISION(){
	}
	void COLLISION::create() {
		SndPlayerBulletVSEnemy = loadSound("../MAIN/assets/game12/SndPlayerBulletVSEnemy.wav");
		SndEnemyBulletVSPlayer = loadSound("../MAIN/assets/game12/SndEnemyBulletVSPlayer.wav");
	}
	//円と矩形(非回転)の当たり判定 ※ロジック by chatGPT
	//数学座標系でも2Dゲーム座標系でも使える
	bool COLLISION::CheckCollision_CircleAABB(
		float cx, float cy,   // 円の中心
		float cr,             // 円の半径
		float rx, float ry,   // 矩形の中心座標
		float rw, float rh    // 矩形の幅と高さ
	) {
		// 円の中心から矩形の最近接点を求める
		float closestX = std::max(rx - rw / 2, std::min(cx, rx + rw / 2));
		float closestY = std::max(ry - rh / 2, std::min(cy, ry + rh / 2));

		// 最近接点と円の中心との距離の2乗を求める
		float dx = cx - closestX;
		float dy = cy - closestY;

		return (dx * dx + dy * dy) <= (cr * cr);
	}

#if 0
//円と矩形(回転あり)との当たり判定 ※ロジック by chatGPT
//数学座標系でも2Dゲーム座標系でも使えるが、回転角は反時計回り前提
//※回転角が時計回りの場合は CheckCollision_CircleOBB() の最後の引数を逆にすればいい
#include <cmath>

	// 2Dベクトル
	struct Vec2 {
		float x, y;

		Vec2 operator-(const Vec2& rhs) const {
			return { x - rhs.x, y - rhs.y };
		}

		Vec2 rotate(float angleRad) const {
			float cosA = std::cos(angleRad);
			float sinA = std::sin(angleRad);
			return {
				x * cosA + y * sinA,
				-x * sinA + y * cosA
			};
		}
	};

	bool CheckCollision_CircleOBB( //円と矩形(回転あり) ※ロジック by chatGPT
		Vec2 circleCenter, float radius,
		Vec2 rectCenter, float halfWidth, float halfHeight, float rotationRad
	) {
		// 1. 円の中心を矩形のローカル空間へ変換
		Vec2 relative = circleCenter - rectCenter;

		// 2. 矩形の逆回転を円に適用
		Vec2 localCircle = relative.rotate(-rotationRad);

		// 3. 通常のAABBと円の当たり判定
		float clampedX = std::max(-halfWidth, std::min(localCircle.x, halfWidth));
		float clampedY = std::max(-halfHeight, std::min(localCircle.y, halfHeight));

		float dx = localCircle.x - clampedX;
		float dy = localCircle.y - clampedY;

		return (dx * dx + dy * dy) <= (radius * radius);
	}
#endif

	bool COLLISION::CheckCollision(class CHARACTER* chL, class CHARACTER* chR) {
		if (chL->shape() == CHARACTER::CS_CIRCLE && chR->shape() == CHARACTER::CS_AABB) {
			float chLScaleBcRadius = chL->bcRadius() * chL->scale();
			float chRScaleBbWidth = chR->bbWidth() * chR->scale();
			float chRScaleBbHeight = chR->bbHeight() * chR->scale();
			bool ret = CheckCollision_CircleAABB(chL->pos().x, chL->pos().y, chLScaleBcRadius,
				chR->pos().x, chR->pos().y, chRScaleBbWidth, chRScaleBbHeight);
			return ret;
		}
		//★PEND; まだ実装してない衝突パターン
		__debugbreak();
		return false;
	}

	void COLLISION::playerBulletsVsEnemies(){
		int playerBullesTotalNum = game()->playerBulletsManager()->totalNum();
		for (int i = 0; i < playerBullesTotalNum; i++){
			BULLET* pb = game()->playerBulletsManager()->bullet(i);
			if (pb->alive()) {
				int enemiesTotalNum = game()->enemiesManager()->totalNum();
				for (int j = 0; j < enemiesTotalNum; j++) {
					ENEMY* e = game()->enemiesManager()->enemy(j);
					if (e->alive()) {
						bool ret = CheckCollision(pb, e);
						if (ret) {
							pb->damage();
							e->damage();
							playSound(SndPlayerBulletVSEnemy);
						}
					}
				}
			}
		}
	}
	void COLLISION::enemiesBulletsVsPlayer() {
		int enemiesBullesTotalNum = game()->enemiesBulletsManager()->totalNum();
		for (int i = 0; i < enemiesBullesTotalNum; i++) {
			BULLET* eb = game()->enemiesBulletsManager()->bullet(i);
			if (eb->alive()) {
				PLAYER* p = game()->player();
				if (p->alive()) {
					bool ret = CheckCollision(eb, p);
					if (ret) {
						eb->damage();
						p->damage();
						playSound(SndEnemyBulletVSPlayer);
					}
				}
			}
		}
	}
}
