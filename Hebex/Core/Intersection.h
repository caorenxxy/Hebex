#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "../ForwardDecl.h"
#include "Geometry.h"

namespace Hebex
{
	class Intersection {
	public:

		Intersection() {}

		Point3f mPosition;
		Vec3f mNormal;
		Vec3f mDpdu, mDpdv;
		Vec3f mDndu, mDndv;
		mutable Vec3f mDpdx, mDpdy;
		mutable float mDudx, mDvdx, mDudy, mDvdy;

		BSDF *mBSDF = nullptr;
		BSSRDF *mBSSRDF = nullptr;
	};
}

#endif