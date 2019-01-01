#ifndef RAY_H
#define RAY_H

#include "../ForwardDecl.h"
#include "Geometry.h"

namespace Hebex 
{
	class Ray {
	public:

		Ray() : tMin(0.f), tMax(INFINITY) {}

		Ray(const Point3f &o, const Vec3f &d, float ptMin = 0.f, float ptMax = INFINITY, const Medium *medium = nullptr):
			mOrigin(o), mDirection(d), tMin(ptMin), tMax(ptMax), mMedium(medium) {}

		Point3f operator()(float t) const { return mOrigin + mDirection * t; }

		friend std::ostream &operator<<(std::ostream &os, const Ray &r) {
			os << "[o=" << r.mOrigin << ", d=" << r.mDirection << ", tMin=" << r.tMin
				<< ", tMax=" << r.tMax << "]";
			return os;
		}

		Point3f mOrigin;
		Vec3f mDirection;
		mutable float tMin, tMax;
		const Medium *mMedium;
	};

	class RayDifferential : public Ray {
	public:

		RayDifferential() { hasDifferentials = false; }

		RayDifferential(const Point3f &o, const Vec3f &d, float ptMin = 0.f, float ptMax = INFINITY, const Medium *medium = nullptr) :
			Ray(o, d, ptMin, ptMax, medium) {
			hasDifferentials = false;
		}

		RayDifferential(const Ray &ray) : Ray(ray) { hasDifferentials = false; }

		void ScaleDifferential(float s) {
			rxOrigin = mOrigin + (rxOrigin - mOrigin) * s;
			ryOrigin = mOrigin + (ryOrigin - mOrigin) * s;
			rxDirection = mDirection + (rxDirection - mDirection) * s;
			ryDirection = mDirection + (ryDirection - mDirection) * s;
		}

		friend std::ostream &operator<<(std::ostream &os, const RayDifferential &r) {
			os << "[ " << (Ray &)r << " has differentials: " <<
				(r.hasDifferentials ? "true" : "false") << ", xo = " << r.rxOrigin <<
				", xd = " << r.rxDirection << ", yo = " << r.ryOrigin << ", yd = " <<
				r.ryDirection;
			return os;
		}

		bool hasDifferentials;
		Point3f rxOrigin, ryOrigin;
		Vec3f rxDirection, ryDirection;
	};
}


#endif
