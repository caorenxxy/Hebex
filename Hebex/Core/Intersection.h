#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "../ForwardDecl.h"
#include "Geometry.h"

namespace Hebex
{
	class Intersection {
	public:

		Intersection() {}
		Intersection(const Point3f &p, const Vec3f &normal, const Vec2f &uv,
			const Vec3f &dpdu, const Vec3f &dpdv, const Vec3f &dndu, const Vec3f &dndv) :
			mPosition(p), mNormal(normal), mUV(uv), mDpdu(dpdu), mDpdv(dpdv), mDndu(dndu), mDndv(dndv) {

		}

		Point3f mPosition;
		Vec3f mNormal;
		Vec2f mUV;
		Vec3f mDpdu, mDpdv;
		Vec3f mDndu, mDndv;
		mutable Vec3f mDpdx, mDpdy;
		mutable float mDudx, mDvdx, mDudy, mDvdy;

		BSDF *mBSDF = nullptr;
		BSSRDF *mBSSRDF = nullptr;
	};
}

#endif