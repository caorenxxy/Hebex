#include "Sampling.h"
#include "Geometry.h"

namespace Hebex
{
	Vec3f UniformSampleSphere(const Point2f &u) {
		float z = 1 - 2 * u[0];
		float r = std::sqrt(std::max(0.f, 1.f - z * z));
		float phi = 2.f * PI * u[1];
		return Vec3f(r * std::cos(phi), r * std::sin(phi), z);
	}

	float UniformSpherePdf() {
		return 1.f / 4 * INV_PI;
	}

	float UniformConePdf(float cosThetaMax) {
		return 1.f / (2.f * PI * (1.f - cosThetaMax));
	}


	Vec3f UniformSampleCone(const Point2f &u, float cosThetaMax) {
		float cosTheta = ((float)1 - u[0]) + u[0] * cosThetaMax;
		float sinTheta = std::sqrt((float)1 - cosTheta * cosTheta);
		float phi = u[1] * 2 * PI;
		return Vec3f(std::cos(phi) * sinTheta, std::sin(phi) * sinTheta,
			cosTheta);
	}

	Vec3f UniformSampleCone(const Point2f &u, float cosThetaMax,
		const Vec3f &x, const Vec3f &y,
		const Vec3f &z) {
		float cosTheta = Lerp(u[0], cosThetaMax, 1.f);
		float sinTheta = std::sqrt((float)1. - cosTheta * cosTheta);
		float phi = u[1] * 2 * PI;
		return std::cos(phi) * sinTheta * x + std::sin(phi) * sinTheta * y +
			cosTheta * z;
	}

}