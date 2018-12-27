#ifndef UTILS_H
#define UTILS_H

/*
#ifndef INFINITY
#define INFINITY FLT_MAX
#endif // INFINITY
*/
#include <stdint.h> 
#include <algorithm>



#if (defined _MSC_VER && _MSC_VER < 1500)
typedef __int8 int8_t;
typedef unsigned __int8 uint8_t;
typedef __int16 int16_t;
typedef unsigned __int16 uint16_t;
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else 
#include <stdint.h> 
#endif

#if defined(_WIN32) || defined(_WIN64)
#include <float.h>
#define isinf(f) (!_finite((f)))
#endif


namespace Hebex
{
	const float PI = 3.14159265358979323f;
	const float TWO_PI = 6.28318530718f;
	const float INV_PI = 0.31830988618379067154f;
	const float INV_TWOPI = 0.15915494309189533577f;


	inline bool IsEqual(float a, float b, const float epsilon = 1e-7f) {
		return fabs(a - b) <= epsilon;
	}

	template <typename T>
	inline bool IsNaN(const T x) {
		return std::isnan(x);
	}

	inline bool IsPowerOf2(uint32_t n) {
		return (n & (n - 1)) == 0;
	}


	inline float Log2(float n) {
		static float invLog2 = 1.0f / logf(2.0f);
		return logf(n) * invLog2;
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

}

#endif
