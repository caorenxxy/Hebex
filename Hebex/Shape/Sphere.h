#ifndef SPHERE_H
#define SPHERE_H

#include "../Core/Shape.h"

namespace Hebex
{
	class Sphere : public Shape {
	public:
		Sphere(const Transform *o2w, const Transform *w2o, float rad);

		BBox ObjectBound() const;

		bool Intersect(const Ray &ray, Intersection *isect) const;

		bool IntersectP(const Ray &ray) const;

		float Area() const;

		Point3f Sample(const Point2f &u, Vec3f *normal) const;

		Point3f Sample(const Point3f &p, const Point2f &u, Vec3f *normal) const;

		float Pdf(const Point3f &p, const Vec3f &wi) const;

	private:
		float mRadius;
		
		const float mThetaMax = PI;
		const float mThetaMin = 0.f;
		const float mPhiMax = 2.f * PI;
		const float mPhiMin = 0.f;
	};
}

#endif