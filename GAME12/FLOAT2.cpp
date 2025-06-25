#include <cmath>
#include "FLOAT2.h"

namespace GAME12 {

	FLOAT2::FLOAT2() {
	}
	FLOAT2::FLOAT2(float x, float y) : x(x), y(y) {
	}
	FLOAT2::~FLOAT2() {
	}
	void FLOAT2::init() {
		x = 0.0f;
		y = 0.0f;
	}
	void FLOAT2::normalize() {
		float mag = sqrtf(x * x + y * y);
		if (mag != 0.0f) {
			x /= mag;
			y /= mag;
		}
		else {
			//WARNING(true, "divide by zero.", "");
			__debugbreak();
		}
	}
	FLOAT2 FLOAT2::operator*(float f) {
		return FLOAT2(x * f, y * f);
	}
	FLOAT2& FLOAT2::operator+=(const class FLOAT2& v) {
		x += v.x;
		y += v.y;
		return *this;
	}

}