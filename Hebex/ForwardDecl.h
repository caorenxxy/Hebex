#ifndef FORWARDDECL_H
#define FORWARDDECL_H

namespace Hebex
{
	template<typename T>
	class Vec3;
	template<typename T>
	class Vec2;
	template <typename T>
	class Point2;
	template <typename T>
	class Point3;
	template <typename T>
	class Normal3;
	typedef Vec2<float> Vec2f;
	typedef Vec2<int> Vec2i;
	typedef Vec3<float> Vec3f;
	typedef Vec3<int> Vec3i;
	typedef Point2<float> Point2f;
	typedef Point2<int> Point2i;
	typedef Point3<float> Point3f;
	typedef Point3<int> Point3i;
	class Transform;
	class BBox;
	class Medium;
	class Ray;
	class Color;
	class MemoryPool;
	class Primitive;
	class BSDF;
	class BSSRDF;
	class Intersection;
	class Shape;
}

#endif