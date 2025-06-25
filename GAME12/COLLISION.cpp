#define NOMINMAX //<algorithim>��<Windows.h>��std::max(), std::min()�ŃG���[���o���̂�������邽�߂ɕK�v by ChatGPT
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
	//�~�Ƌ�`(���])�̓����蔻�� �����W�b�N by chatGPT
	//���w���W�n�ł�2D�Q�[�����W�n�ł��g����
	bool COLLISION::CheckCollision_CircleAABB(
		float cx, float cy,   // �~�̒��S
		float cr,             // �~�̔��a
		float rx, float ry,   // ��`�̒��S���W
		float rw, float rh    // ��`�̕��ƍ���
	) {
		// �~�̒��S�����`�̍ŋߐړ_�����߂�
		float closestX = std::max(rx - rw / 2, std::min(cx, rx + rw / 2));
		float closestY = std::max(ry - rh / 2, std::min(cy, ry + rh / 2));

		// �ŋߐړ_�Ɖ~�̒��S�Ƃ̋�����2������߂�
		float dx = cx - closestX;
		float dy = cy - closestY;

		return (dx * dx + dy * dy) <= (cr * cr);
	}

#if 0
//�~�Ƌ�`(��]����)�Ƃ̓����蔻�� �����W�b�N by chatGPT
//���w���W�n�ł�2D�Q�[�����W�n�ł��g���邪�A��]�p�͔����v���O��
//����]�p�����v���̏ꍇ�� CheckCollision_CircleOBB() �̍Ō�̈������t�ɂ���΂���
#include <cmath>

	// 2D�x�N�g��
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

	bool CheckCollision_CircleOBB( //�~�Ƌ�`(��]����) �����W�b�N by chatGPT
		Vec2 circleCenter, float radius,
		Vec2 rectCenter, float halfWidth, float halfHeight, float rotationRad
	) {
		// 1. �~�̒��S����`�̃��[�J����Ԃ֕ϊ�
		Vec2 relative = circleCenter - rectCenter;

		// 2. ��`�̋t��]���~�ɓK�p
		Vec2 localCircle = relative.rotate(-rotationRad);

		// 3. �ʏ��AABB�Ɖ~�̓����蔻��
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
		//��PEND; �܂��������ĂȂ��Փ˃p�^�[��
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
