#pragma once

namespace GAME12 {

	class FLOAT2
	{
	public:
		float x = 0.0f;
		float y = 0.0f;
		FLOAT2();
		FLOAT2(float x, float y);
		~FLOAT2();
		void init();
		void normalize();
		FLOAT2 operator*(float f);
		FLOAT2& operator+=(const class FLOAT2& v);
	};

}
