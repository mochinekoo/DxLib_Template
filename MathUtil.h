#pragma once
#include <cmath>
#include "Vector2D.h"

namespace MathUtilty {

	const float PI = 3.1415926535f;

	//ベクトルの向きをラジアンで返す
	inline float Angle(Vector2D vec) {
		return std::atan2(vec.GetY(), vec.GetX());
	}

	//ラジアンから単位行列
	inline Vector2D FromAngle(float angle) {
		return Vector2D(std::cos(angle), std::sin(angle));
	}

	//内積
	inline float Dot(Vector2D& a, Vector2D b) {
		return a.GetX() * b.GetX() + a.GetY() * b.GetY();
	}

	//外積
	inline float Cross(Vector2D a, Vector2D b) {
		return a.GetX() * b.GetY() - a.GetY() * b.GetX();
	}
}