#ifndef BBOX_H
#define BBOX_H

#include "Geometry.h"

namespace Hebex
{
	class BBox {
	public:
		BBox() {
			pMin = Point3f(INFINITY, INFINITY, INFINITY);
			pMax = Point3f(-INFINITY, -INFINITY, -INFINITY);
		}

		BBox(const Point3f &p) : pMin(p), pMax(p) { }

		BBox(const Point3f &p1, const Point3f &p2) {
			pMin = Point3f(std::min(p1.x, p2.x), std::min(p1.y, p2.y), std::min(p1.z, p2.z));
			pMax = Point3f(std::max(p1.x, p2.x), std::max(p1.y, p2.y), std::max(p1.z, p2.z));
		}

		friend BBox Union(const BBox &b, const Point3f &p);

		friend BBox Union(const BBox &b, const BBox &b2);

		bool Overlaps(const BBox &b) const {
			bool x = (pMax.x >= b.pMin.x) && (pMin.x <= b.pMax.x);
			bool y = (pMax.y >= b.pMin.y) && (pMin.y <= b.pMax.y);
			bool z = (pMax.z >= b.pMin.z) && (pMin.z <= b.pMax.z);
			return (x && y && z);
		}

		bool Inside(const Point3f &pt) const {
			return (pt.x >= pMin.x && pt.x <= pMax.x &&
				pt.y >= pMin.y && pt.y <= pMax.y &&
				pt.z >= pMin.z && pt.z <= pMax.z);
		}

		void Expand(float delta) {
			pMin -= Vec3f(delta, delta, delta);
			pMax += Vec3f(delta, delta, delta);
		}

		float SurfaceArea() const {
			Vec3f d = pMax - pMin;
			return 2.f * (d.x * d.y + d.x * d.z + d.y * d.z);
		}

		float Volume() const {
			Vec3f d = pMax - pMin;
			return d.x * d.y * d.z;
		}

		int MaximumExtent() const {
			Vec3f diag = pMax - pMin;
			if (diag.x > diag.y && diag.x > diag.z)
				return 0;
			else if (diag.y > diag.z)
				return 1;
			else
				return 2;
		}

		const Point3f &operator[](int i) const;

		Point3f &operator[](int i);

		Point3f Lerp(float tx, float ty, float tz) const {
			return Point3f(Hebex::Lerp(tx, pMin.x, pMax.x), Hebex::Lerp(ty, pMin.y, pMax.y),
				Hebex::Lerp(tz, pMin.z, pMax.z));
		}

		Vec3f Offset(const Point3f &p) const {
			return Vec3f((p.x - pMin.x) / (pMax.x - pMin.x),
				(p.y - pMin.y) / (pMax.y - pMin.y),
				(p.z - pMin.z) / (pMax.z - pMin.z));
		}

		void BoundingSphere(Point3f *c, float *rad) const;

		bool IntersectP(const Ray &ray, float *hitt0 = NULL, float *hitt1 = NULL) const;

		bool operator==(const BBox &b) const {
			return b.pMin == pMin && b.pMax == pMax;
		}
		bool operator!=(const BBox &b) const {
			return b.pMin != pMin || b.pMax != pMax;
		}

		Point3f pMin, pMax;
	};

	inline const Point3f &BBox::operator[](int i) const
	{
		return (&pMin)[i];
	}


	inline Point3f &BBox::operator[](int i)
	{
		return (&pMin)[i];
	}
}


#endif
