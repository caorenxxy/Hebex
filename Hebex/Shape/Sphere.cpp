#include "Sphere.h"
#include "../Core/Transform.h"
#include "../Core/Intersection.h"
#include "../Core/Sampling.h"

namespace Hebex
{
	Sphere::Sphere(const Transform *o2w, const Transform *w2o, float rad) :
		Shape(o2w, w2o), mRadius(rad) {
	}

	bool Sphere::Intersect(const Ray &ray, Intersection *isect) const {
		Ray r;
		(*WorldToObject)(ray, &r);

		//Compute qudratic sphere coefficients
		float A = r.mDirection.x * r.mDirection.x + r.mDirection.y * r.mDirection.y + r.mDirection.z * r.mDirection.z;
		float B = 2.f * (r.mDirection.x * r.mOrigin.x + r.mDirection.y * r.mOrigin.y + r.mDirection.z * r.mOrigin.z);
		float C = r.mOrigin.x * r.mOrigin.x + r.mOrigin.y * r.mOrigin.y + ray.mOrigin.z * ray.mOrigin.z - mRadius * mRadius;

		float t0, t1;
		if (!Quadratic(A, B, C, &t0, &t1)) return false;

		if (t0 > r.tMax || t1 < r.tMin) return false;

		float tHit = t0;
		if (t0 < r.tMin) {
			tHit = t1;
			if (tHit > ray.tMax) return false;
		}

		Point3f pHit = r(tHit);
		if (pHit.x == 0.f && pHit.y == 0.f) pHit.x = 1e-5f * mRadius;
		float phi = std::atan2f(pHit.y, pHit.x);
		if (phi < 0.) phi += 2.f * INV_PI;

		float u = phi / mPhiMax;
		float theta = std::acosf(Clamp(pHit.z / mRadius, -1.f, 1.f));
		float v = (theta - mThetaMin) / (mThetaMax - mThetaMin);

		//dpdu, dpdv
		float zRadius = std::sqrtf(pHit.x * pHit.x + pHit.y * pHit.y);
		float invzRadius = 1.f / zRadius;
		float cosPhi = pHit.x * invzRadius;
		float sinPhi = pHit.y * invzRadius;
		Vec3f dpdu(-mPhiMax * pHit.y, mPhiMax * pHit.x, 0.f);
		Vec3f dpdv = (mThetaMax - mThetaMin) * 
			Vec3f(pHit.z * cosPhi, pHit.z * sinPhi, -mRadius * std::sinf(theta));

		//dndu, dndv
		Vec3f d2Pduu = -mPhiMax * mPhiMax * Vec3f(pHit.x, pHit.y, 0.f);
		Vec3f d2Pduv = (mThetaMax - mThetaMin) * pHit.z * pHit.z * mPhiMax * Vec3f(-sinPhi, cosPhi, 0.f);
		Vec3f d2Pdvv = -(mThetaMax - mThetaMin) * (mThetaMax - mThetaMin) * Vec3f(pHit.x, pHit.y, pHit.z);

		float E = Dot(dpdu, dpdu);
		float F = Dot(dpdu, dpdv);
		float G = Dot(dpdv, dpdv);
		Vec3f N = Normalize(Cross(dpdu, dpdv));
		float e = Dot(N, d2Pduu);
		float f = Dot(N, d2Pduv);
		float g = Dot(N, d2Pdvv);

		float invEGF2 = 1.f / (E*G - F * F);
		Vec3f dndu = Vec3f((f * F - e * G) * invEGF2 * dpdu +
			(e * F - f * E) * invEGF2 * dpdv);
		Vec3f dndv = Vec3f((g*F - f * G) * invEGF2 * dpdu +
			(f * F - g * E) * invEGF2 * dpdv);

		Vec3f normal = pHit - Point3f(0, 0, 0);

		const Transform &o2w = *ObjectToWorld;
		const Transform o2wN = TransformNormal(o2w);
		*isect = std::move(Intersection(o2w(pHit), o2wN(normal), Vec2f(u, v), o2w(dpdu), o2w(dpdv), o2wN(dndu), o2wN(dndv)));
		return true;
	}

	bool Sphere::IntersectP(const Ray &ray) const {
		Ray r;
		(*WorldToObject)(ray, &r);

		//Compute qudratic sphere coefficients
		float A = r.mDirection.x * r.mDirection.x + r.mDirection.y * r.mDirection.y + r.mDirection.z * r.mDirection.z;
		float B = 2.f * (r.mDirection.x * r.mOrigin.x + r.mDirection.y * r.mOrigin.y + r.mDirection.z * r.mOrigin.z);
		float C = r.mOrigin.x * r.mOrigin.x + r.mOrigin.y * r.mOrigin.y + ray.mOrigin.z * ray.mOrigin.z - mRadius * mRadius;

		float t0, t1;
		if (!Quadratic(A, B, C, &t0, &t1)) return false;

		if (t0 > r.tMax || t1 < r.tMin) return false;

		float tHit = t0;
		if (t0 < r.tMin) {
			tHit = t1;
			if (tHit > ray.tMax) return false;
		}

		return true;
	}

	BBox Sphere::ObjectBound() const {
		return BBox(Point3f(-mRadius, -mRadius, -mRadius),
			Point3f(mRadius, mRadius, mRadius));
	}

	float Sphere::Area() const {
		return 4.f * mRadius * mRadius * PI;
	}

	Point3f Sphere::Sample(const Point2f &u, Vec3f *normal) const {
		Point3f p = Point3f(0, 0, 0) + mRadius * UniformSampleSphere(u);
		Transform transformNormal = TransformNormal((*ObjectToWorld));
		*normal = transformNormal(Vec3f(p.x, p.y, p.z));

		return (*ObjectToWorld)(p);
	}

	Point3f Sphere::Sample(const Point3f &p, const Point2f &u, Vec3f *normal) const {
		Point3f pCenter = (*ObjectToWorld)(Point3f(0, 0, 0));
		Vec3f wc = Normalize(pCenter - p);
		Vec3f wcX, wcY;
		CoordinateSystem(wc, &wcX, &wcY);

		if (DistanceSquared(p, pCenter) - mRadius * mRadius < 1e-4f)
			return Sample(u, normal);

		// Sample sphere uniformly inside subtended cone
		float sinThetaMax2 = mRadius * mRadius / DistanceSquared(p, pCenter);
		float cosThetaMax = sqrtf(std::max(0.f, 1.f - sinThetaMax2));
		//float thit, rayEpsilon;
		Point3f pHit;
		Intersection isect;
		Ray ray(p, UniformSampleCone(u, cosThetaMax, wcX, wcY, wc), 1e-3f);
		if (!Intersect(ray, &isect))
			pHit = isect.mPosition;
		*normal = Vec3f(Normalize(pHit - pCenter));
		return pHit;
	}

	float Sphere::Pdf(const Point3f &p, const Vec3f &wi) const {
		Point3f pCenter = (*ObjectToWorld)(Point3f(0, 0, 0));

		if (DistanceSquared(p, pCenter) - mRadius * mRadius < 1e-4f)
			return Shape::Pdf(p, wi);

		float sinThetaMax2 = mRadius * mRadius / DistanceSquared(p, pCenter);
		float cosThetaMax = std::sqrtf(std::max(0.f, 1.f - sinThetaMax2));
		return UniformConePdf(cosThetaMax);
	}
}