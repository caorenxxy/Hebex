#ifndef UTILS_H
#define UTILS_H
/*
#ifndef INFINITY
#define INFINITY FLT_MAX
#endif // INFINITY
*/
//#include <stdint.h> 
#include "Hebex.h"





namespace Hebex
{
	const float PI = 3.14159265358979323f;
	const float TWO_PI = 6.28318530718f;
	const float INV_PI = 0.31830988618379067154f;
	const float INV_TWOPI = 0.15915494309189533577f;


	inline bool IsEqual(float a, float b, const float epsilon = 1e-7f) {
		return std::fabs(a - b) <= epsilon;
	}

	template <typename T>
	inline bool IsNaN(const T x) {
		return std::isnan(x);
	}

	template <typename T>
	inline constexpr bool IsPowerOf2(T v) {
		return v && !(v & (v - 1));
	}


	inline float Log2(float n) {
		static float invLog2 = 1.0f / logf(2.0f);
		return std::logf(n) * invLog2;
	}

	inline float Clamp(float f, float low, float high) {
		if (f < low) {
			return low;
		}
		else if (f > high) {
			return high;
		}
		else return f;
	}

	inline int Clamp(int f, int low, int high) {
		if (f < low) {
			return low;
		}
		else if (f > high) {
			return high;
		}
		else return f;
	}

	inline float Lerp(float t, float v1, float v2) {
		return (1.f - t) * v1 + t * v2;
	}

	inline float Radians(float deg) {
		return ((float)PI / 180.f) * deg;
	}

	inline bool Quadratic(float A, float B, float C, float *t0, float *t1) {
		// Find quadratic discriminant
		float discrim = B * B - 4.f * A * C;
		if (discrim < 0.) return false;
		float rootDiscrim = sqrtf(discrim);

		// Compute quadratic _t_ values
		float q;
		if (B < 0) q = -.5f * (B - rootDiscrim);
		else       q = -.5f * (B + rootDiscrim);
		*t0 = q / A;
		*t1 = C / q;
		if (*t0 > *t1) std::swap(*t0, *t1);
		return true;
	}
}

#endif
