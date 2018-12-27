#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "Utils.h"
#include "Hebex.h"
#include "../ForwardDecl.h"

namespace Hebex 
{
	template <typename T>
	class Vec2 {
	public:
		Vec2() { x = y = 0; }

		Vec2(T xx, T yy) : x(xx), y(yy) {}

		bool HasNaNs() const { return IsNaN(x) || IsNaN(y); }

		explicit Vec2(const Point2<T> &p);

		explicit Vec2(const Point3<T> &p);

		Vec2(const Vec2<T> &v) {
			x = v.x;
			y = v.y;
		}
		Vec2<T> &operator=(const Vec2<T> &v) {
			x = v.x;
			y = v.y;
			return *this;
		}

		Vec2<T> operator+(const Vec2<T> &v) const {
			return Vec2(x + v.x, y + v.y);
		}

		Vec2<T> &operator+=(const Vec2<T> &v) {
			x += v.x;
			y += v.y;
			return *this;
		}

		Vec2<T> operator-(const Vec2<T> &v) const {
			return Vec2(x - v.x, y - v.y);
		}

		Vec2<T> operator-=(const Vec2<T> &v) {
			x -= v.x;
			y -= v.y;
			return *this;
		}

		bool operator==(const Vec2<T> &v) const { return x == v.x && y == v.y; }

		bool operator!=(const Vec2<T> &v) const { return x != v.x || y != v.y; }

		template <typename U>
		Vec2<T> operator*(U f) const {
			return Vec2<T>(f * x, f * y);
		}

		template <typename U>
		Vec2<T> &operator*=(U f) {
			x *= f;
			y *= f;
			return *this;
		}

		template <typename U>
		Vec2<T> operator/(U f) const {
			float inv = 1.0f / f;
			return Vec2<T>(x * inv, y * inv);
		}

		Vec2<T> operator-() const { return Vec2<T>(-x, -y); }

		T operator[](int i) const {
			if (i == 0) return x;
			return y;
		}

		float LengthSquared() const { return x * x + y * y; }

		float Length() const { return std::sqrt(LengthSquared()); }

		T x, y;
	};

	template <typename T>
	inline std::ostream &operator<<(std::ostream &os, const Vec2<T> &v) {
		os << "[ " << v.x << ", " << v.y << " ]";
		return os;
	}


	

	template <typename T>
	class Vec3 {
	public:
		// Vec3 Public Methods
		T operator[](int i) const {
			if (i == 0) return x;
			if (i == 1) return y;
			return z;
		}

		T &operator[](int i) {
			if (i == 0) return x;
			if (i == 1) return y;
			return z;
		}

		Vec3() { x = y = z = 0; }

		Vec3(T x, T y, T z) : x(x), y(y), z(z) {  }

		bool HasNaNs() const { return isNaN(x) || isNaN(y) || isNaN(z); }

		explicit Vec3(const Point3<T> &p);

		Vec3(const Vec3<T> &v) {
			x = v.x;
			y = v.y;
			z = v.z;
		}

		Vec3<T> &operator=(const Vec3<T> &v) {
			x = v.x;
			y = v.y;
			z = v.z;
			return *this;
		}

		Vec3<T> operator+(const Vec3<T> &v) const {
			return Vec3(x + v.x, y + v.y, z + v.z);
		}

		Vec3<T> &operator+=(const Vec3<T> &v) {
			x += v.x;
			y += v.y;
			z += v.z;
			return *this;
		}

		Vec3<T> operator-(const Vec3<T> &v) const {
			return Vec3(x - v.x, y - v.y, z - v.z);
		}

		Vec3<T> &operator-=(const Vec3<T> &v) {
			x -= v.x;
			y -= v.y;
			z -= v.z;
			return *this;
		}

		bool operator==(const Vec3<T> &v) const {
			return x == v.x && y == v.y && z == v.z;
		}

		bool operator!=(const Vec3<T> &v) const {
			return x != v.x || y != v.y || z != v.z;
		}

		template <typename U>
		Vec3<T> operator*(U s) const {
			return Vec3<T>(s * x, s * y, s * z);
		}

		template <typename U>
		Vec3<T> &operator*=(U s) {
			x *= s;
			y *= s;
			z *= s;
			return *this;
		}

		template <typename U>
		Vec3<T> operator/(U f) const {
			float inv = 1.0f / f;
			return Vec3<T>(x * inv, y * inv, z * inv);
		}

		template <typename U>
		Vec3<T> &operator/=(U f) {
			float inv = 1.0f / f;
			x *= inv;
			y *= inv;
			z *= inv;
			return *this;
		}

		Vec3<T> operator-() const { return Vec3<T>(-x, -y, -z); }

		float LengthSquared() const { return x * x + y * y + z * z; }

		float Length() const { return std::sqrt(LengthSquared()); }

		explicit Vec3(const Normal3<T> &n);

		// Vector3 Public Data
		T x, y, z;
	};

	template <typename T>
	inline std::ostream &operator<<(std::ostream &os, const Vec3<T> &v) {
		os << "[ " << v.x << ", " << v.y << ", " << v.z << " ]";
		return os;
	}

	typedef Vec2<float> Vec2f;
	typedef Vec2<int> Vec2i;
	typedef Vec3<float> Vec3f;
	typedef Vec3<int> Vec3i;

	
	// Point Declarations
	template <typename T>
	class Point2 {
	public:
		// Point2 Public Methods
		explicit Point2(const Point3<T> &p) : x(p.x), y(p.y) { }

		Point2() { x = y = 0; }

		Point2(T xx, T yy) : x(xx), y(yy) { }

		template <typename U>
		explicit Point2(const Point2<U> &p) {
			x = (T)p.x;
			y = (T)p.y;
		}

		template <typename U>
		explicit Point2(const Vec2<U> &p) {
			x = (T)p.x;
			y = (T)p.y;
		}

		template <typename U>
		explicit operator Vec2<U>() const {
			return Vec2<U>(x, y);
		}

		Point2(const Point2<T> &p) {
			x = p.x;
			y = p.y;
		}

		Point2<T> &operator=(const Point2<T> &p) {
			x = p.x;
			y = p.y;
			return *this;
		}

		Point2<T> operator+(const Vec2<T> &v) const {
			return Point2<T>(x + v.x, y + v.y);
		}

		Point2<T> &operator+=(const Vec2<T> &v) {
			x += v.x;
			y += v.y;
			return *this;
		}

		Vec2<T> operator-(const Point2<T> &p) const {
			return Vec2<T>(x - p.x, y - p.y);
		}

		Point2<T> operator-(const Vec2<T> &v) const {
			return Point2<T>(x - v.x, y - v.y);
		}

		Point2<T> operator-() const { return Point2<T>(-x, -y); }

		Point2<T> &operator-=(const Vec2<T> &v) {
			x -= v.x;
			y -= v.y;
			return *this;
		}
		Point2<T> &operator+=(const Point2<T> &p) {
			x += p.x;
			y += p.y;
			return *this;
		}
		Point2<T> operator+(const Point2<T> &p) const {
			return Point2<T>(x + p.x, y + p.y);
		}

		template <typename U>
		Point2<T> operator*(U f) const {
			return Point2<T>(f * x, f * y);
		}

		template <typename U>
		Point2<T> &operator*=(U f) {
			x *= f;
			y *= f;
			return *this;
		}

		template <typename U>
		Point2<T> operator/(U f) const {
			float inv = 1.0f / f;
			return Point2<T>(inv * x, inv * y);
		}

		template <typename U>
		Point2<T> &operator/=(U f) {
			float inv = 1.0f / f;
			x *= inv;
			y *= inv;
			return *this;
		}

		T operator[](int i) const {
			if (i == 0) return x;
			return y;
		}

		T &operator[](int i) {
			if (i == 0) return x;
			return y;
		}
		bool operator==(const Point2<T> &p) const { return x == p.x && y == p.y; }

		bool operator!=(const Point2<T> &p) const { return x != p.x || y != p.y; }

		bool HasNaNs() const { return IsNaN(x) || IsNaN(y); }

		// Point2 Public Data
		T x, y;
	};

	
	template <typename T>
	class Point3 {
	public:
		// Point3 Public Methods
		Point3() { x = y = z = 0; }

		Point3(T x, T y, T z) : x(x), y(y), z(z) {  }

		template <typename U>
		explicit Point3(const Point3<U> &p)
			: x((T)p.x), y((T)p.y), z((T)p.z) {
		}

		template <typename U>
		explicit operator Vec3<U>() const {
			return Vec3<U>(x, y, z);
		}

		Point3(const Point3<T> &p) {
			x = p.x;
			y = p.y;
			z = p.z;
		}

		Point3<T> &operator=(const Point3<T> &p) {
			x = p.x;
			y = p.y;
			z = p.z;
			return *this;
		}

		Point3<T> operator+(const Vec3<T> &v) const {
			return Point3<T>(x + v.x, y + v.y, z + v.z);
		}

		Point3<T> &operator+=(const Vec3<T> &v) {
			x += v.x;
			y += v.y;
			z += v.z;
			return *this;
		}

		Vec3<T> operator-(const Point3<T> &p) const {
			return Vec3<T>(x - p.x, y - p.y, z - p.z);
		}

		Point3<T> operator-(const Vec3<T> &v) const {
			return Point3<T>(x - v.x, y - v.y, z - v.z);
		}

		Point3<T> &operator-=(const Vec3<T> &v) {
			x -= v.x;
			y -= v.y;
			z -= v.z;
			return *this;
		}

		Point3<T> &operator+=(const Point3<T> &p) {
			x += p.x;
			y += p.y;
			z += p.z;
			return *this;
		}

		Point3<T> operator+(const Point3<T> &p) const {
			return Point3<T>(x + p.x, y + p.y, z + p.z);
		}

		template <typename U>
		Point3<T> operator*(U f) const {
			return Point3<T>(f * x, f * y, f * z);
		}

		template <typename U>
		Point3<T> &operator*=(U f) {
			x *= f;
			y *= f;
			z *= f;
			return *this;
		}

		template <typename U>
		Point3<T> operator/(U f) const {
			float inv = 1.0f / f;
			return Point3<T>(inv * x, inv * y, inv * z);
		}

		template <typename U>
		Point3<T> &operator/=(U f) {
			float inv = 1.0f / f;
			x *= inv;
			y *= inv;
			z *= inv;
			return *this;
		}

		T operator[](int i) const {
			if (i == 0) return x;
			if (i == 1) return y;
			return z;
		}

		T &operator[](int i) {
			if (i == 0) return x;
			if (i == 1) return y;
			return z;
		}

		bool operator==(const Point3<T> &p) const {
			return x == p.x && y == p.y && z == p.z;
		}

		bool operator!=(const Point3<T> &p) const {
			return x != p.x || y != p.y || z != p.z;
		}

		bool HasNaNs() const { return IsNaN(x) || IsNaN(y) || IsNaN(z); }

		Point3<T> operator-() const { return Point3<T>(-x, -y, -z); }

		// Point3 Public Data
		T x, y, z;
	};

	template <typename T>
	inline std::ostream &operator<<(std::ostream &os, const Point3<T> &v) {
		os << "[ " << v.x << ", " << v.y << ", " << v.z << " ]";
		return os;
	}

	typedef Point2<float> Point2f;
	typedef Point2<int> Point2i;
	typedef Point3<float> Point3f;
	typedef Point3<int> Point3i;

	
	// Normal Declarations
	template <typename T>
	class Normal3 {
	public:
		// Normal3 Public Methods
		Normal3() { x = y = z = 0; }

		Normal3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {  }

		Normal3<T> operator-() const { return Normal3(-x, -y, -z); }

		Normal3<T> operator+(const Normal3<T> &n) const {
			return Normal3<T>(x + n.x, y + n.y, z + n.z);
		}

		Normal3<T> &operator+=(const Normal3<T> &n) {
			x += n.x;
			y += n.y;
			z += n.z;
			return *this;
		}
		Normal3<T> operator-(const Normal3<T> &n) const {
			return Normal3<T>(x - n.x, y - n.y, z - n.z);
		}

		Normal3<T> &operator-=(const Normal3<T> &n) {
			x -= n.x;
			y -= n.y;
			z -= n.z;
			return *this;
		}

		bool HasNaNs() const { return IsNaN(x) || IsNaN(y) || IsNaN(z); }

		template <typename U>
		Normal3<T> operator*(U f) const {
			return Normal3<T>(f * x, f * y, f * z);
		}

		template <typename U>
		Normal3<T> &operator*=(U f) {
			x *= f;
			y *= f;
			z *= f;
			return *this;
		}
		template <typename U>
		Normal3<T> operator/(U f) const {
			float inv = 1.0f / f;
			return Normal3<T>(x * inv, y * inv, z * inv);
		}

		template <typename U>
		Normal3<T> &operator/=(U f) {
			float inv = 1.0 / f;
			x *= inv;
			y *= inv;
			z *= inv;
			return *this;
		}
		float LengthSquared() const { return x * x + y * y + z * z; }
		float Length() const { return std::sqrt(LengthSquared()); }

		Normal3<T>(const Normal3<T> &n) {
			x = n.x;
			y = n.y;
			z = n.z;
		}

		Normal3<T> &operator=(const Normal3<T> &n) {
			x = n.x;
			y = n.y;
			z = n.z;
			return *this;
		}

		explicit Normal3<T>(const Vec3<T> &v) : x(v.x), y(v.y), z(v.z) {
			DCHECK(!v.HasNaNs());
		}
		bool operator==(const Normal3<T> &n) const {
			return x == n.x && y == n.y && z == n.z;
		}
		bool operator!=(const Normal3<T> &n) const {
			return x != n.x || y != n.y || z != n.z;
		}

		T operator[](int i) const {
			if (i == 0) return x;
			if (i == 1) return y;
			return z;
		}

		T &operator[](int i) {
			if (i == 0) return x;
			if (i == 1) return y;
			return z;
		}

		// Normal3 Public Data
		T x, y, z;
	};

	template <typename T>
	inline std::ostream &operator<<(std::ostream &os, const Normal3<T> &v) {
		os << "[ " << v.x << ", " << v.y << ", " << v.z << " ]";
		return os;
	}

	typedef Normal3<float> Normal3f;


	template <typename T>
	inline Vec3<T>::Vec3(const Point3<T> &p)
		: x(p.x), y(p.y), z(p.z) {
	}

	template <typename T, typename U>
	inline Vec3<T> operator*(U s, const Vec3<T> &v) {
		return v * s;
	}
	template <typename T>
	Vec3<T> Abs(const Vec3<T> &v) {
		return Vec3<T>(std::abs(v.x), std::abs(v.y), std::abs(v.z));
	}

	template <typename T>
	inline T Dot(const Vec3<T> &v1, const Vec3<T> &v2) {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	template <typename T>
	inline T AbsDot(const Vec3<T> &v1, const Vec3<T> &v2) {
		return std::abs(Dot(v1, v2));
	}

	template <typename T>
	inline Vec3<T> Cross(const Vec3<T> &v1, const Vec3<T> &v2) {
		double v1x = v1.x, v1y = v1.y, v1z = v1.z;
		double v2x = v2.x, v2y = v2.y, v2z = v2.z;
		return Vec3<T>((v1y * v2z) - (v1z * v2y), (v1z * v2x) - (v1x * v2z),
			(v1x * v2y) - (v1y * v2x));
	}

	template <typename T>
	inline Vec3<T> Cross(const Vec3<T> &v1, const Normal3<T> &v2) {
		double v1x = v1.x, v1y = v1.y, v1z = v1.z;
		double v2x = v2.x, v2y = v2.y, v2z = v2.z;
		return Vec3<T>((v1y * v2z) - (v1z * v2y), (v1z * v2x) - (v1x * v2z),
			(v1x * v2y) - (v1y * v2x));
	}

	template <typename T>
	inline Vec3<T> Cross(const Normal3<T> &v1, const Vec3<T> &v2) {
		double v1x = v1.x, v1y = v1.y, v1z = v1.z;
		double v2x = v2.x, v2y = v2.y, v2z = v2.z;
		return Vec3<T>((v1y * v2z) - (v1z * v2y), (v1z * v2x) - (v1x * v2z),
			(v1x * v2y) - (v1y * v2x));
	}

	template <typename T>
	inline Vec3<T> Normalize(const Vec3<T> &v) {
		return v / v.Length();
	}
	template <typename T>
	T MinComponent(const Vec3<T> &v) {
		return std::min(v.x, std::min(v.y, v.z));
	}

	template <typename T>
	T MaxComponent(const Vec3<T> &v) {
		return std::max(v.x, std::max(v.y, v.z));
	}

	template <typename T>
	int MaxDimension(const Vec3<T> &v) {
		return (v.x > v.y) ? ((v.x > v.z) ? 0 : 2) : ((v.y > v.z) ? 1 : 2);
	}

	template <typename T>
	Vec3<T> Min(const Vec3<T> &p1, const Vec3<T> &p2) {
		return Vec3<T>(std::min(p1.x, p2.x), std::min(p1.y, p2.y),
			std::min(p1.z, p2.z));
	}

	template <typename T>
	Vec3<T> Max(const Vec3<T> &p1, const Vec3<T> &p2) {
		return Vec3<T>(std::max(p1.x, p2.x), std::max(p1.y, p2.y),
			std::max(p1.z, p2.z));
	}

	template <typename T>
	Vec3<T> Permute(const Vec3<T> &v, int x, int y, int z) {
		return Vec3<T>(v[x], v[y], v[z]);
	}

	template <typename T>
	inline void CoordinateSystem(const Vec3<T> &v1, Vec3<T> *v2,
		Vec3<T> *v3) {
		if (std::abs(v1.x) > std::abs(v1.y))
			*v2 = Vec3<T>(-v1.z, 0, v1.x) / std::sqrt(v1.x * v1.x + v1.z * v1.z);
		else
			*v2 = Vec3<T>(0, v1.z, -v1.y) / std::sqrt(v1.y * v1.y + v1.z * v1.z);
		*v3 = Cross(v1, *v2);
	}

	template <typename T>
	Vec2<T>::Vec2(const Point2<T> &p)
		: x(p.x), y(p.y) {
	}

	template <typename T>
	Vec2<T>::Vec2(const Point3<T> &p)
		: x(p.x), y(p.y) {
	}

	template <typename T, typename U>
	inline Vec2<T> operator*(U f, const Vec2<T> &v) {
		return v * f;
	}
	template <typename T>
	inline float Dot(const Vec2<T> &v1, const Vec2<T> &v2) {
		return v1.x * v2.x + v1.y * v2.y;
	}

	template <typename T>
	inline float AbsDot(const Vec2<T> &v1, const Vec2<T> &v2) {
		return std::abs(Dot(v1, v2));
	}

	template <typename T>
	inline Vec2<T> Normalize(const Vec2<T> &v) {
		return v / v.Length();
	}
	template <typename T>
	Vec2<T> Abs(const Vec2<T> &v) {
		return Vec2<T>(std::abs(v.x), std::abs(v.y));
	}

	template <typename T>
	inline float Distance(const Point3<T> &p1, const Point3<T> &p2) {
		return (p1 - p2).Length();
	}

	template <typename T>
	inline float DistanceSquared(const Point3<T> &p1, const Point3<T> &p2) {
		return (p1 - p2).LengthSquared();
	}

	template <typename T, typename U>
	inline Point3<T> operator*(U f, const Point3<T> &p) {
		return p * f;
	}

	template <typename T>
	Point3<T> Lerp(float t, const Point3<T> &p0, const Point3<T> &p1) {
		return (1 - t) * p0 + t * p1;
	}

	template <typename T>
	Point3<T> Min(const Point3<T> &p1, const Point3<T> &p2) {
		return Point3<T>(std::min(p1.x, p2.x), std::min(p1.y, p2.y),
			std::min(p1.z, p2.z));
	}

	template <typename T>
	Point3<T> Max(const Point3<T> &p1, const Point3<T> &p2) {
		return Point3<T>(std::max(p1.x, p2.x), std::max(p1.y, p2.y),
			std::max(p1.z, p2.z));
	}

	template <typename T>
	Point3<T> Floor(const Point3<T> &p) {
		return Point3<T>(std::floor(p.x), std::floor(p.y), std::floor(p.z));
	}

	template <typename T>
	Point3<T> Ceil(const Point3<T> &p) {
		return Point3<T>(std::ceil(p.x), std::ceil(p.y), std::ceil(p.z));
	}

	template <typename T>
	Point3<T> Abs(const Point3<T> &p) {
		return Point3<T>(std::abs(p.x), std::abs(p.y), std::abs(p.z));
	}

	template <typename T>
	inline float Distance(const Point2<T> &p1, const Point2<T> &p2) {
		return (p1 - p2).Length();
	}

	template <typename T>
	inline float DistanceSquared(const Point2<T> &p1, const Point2<T> &p2) {
		return (p1 - p2).LengthSquared();
	}

	template <typename T, typename U>
	inline Point2<T> operator*(U f, const Point2<T> &p) {
		return p * f;
	}

	template <typename T>
	Point2<T> Floor(const Point2<T> &p) {
		return Point2<T>(std::floor(p.x), std::floor(p.y));
	}

	template <typename T>
	Point2<T> Ceil(const Point2<T> &p) {
		return Point2<T>(std::ceil(p.x), std::ceil(p.y));
	}

	template <typename T>
	Point2<T> Lerp(float t, const Point2<T> &v0, const Point2<T> &v1) {
		return (1 - t) * v0 + t * v1;
	}

	template <typename T>
	Point2<T> Min(const Point2<T> &pa, const Point2<T> &pb) {
		return Point2<T>(std::min(pa.x, pb.x), std::min(pa.y, pb.y));
	}

	template <typename T>
	Point2<T> Max(const Point2<T> &pa, const Point2<T> &pb) {
		return Point2<T>(std::max(pa.x, pb.x), std::max(pa.y, pb.y));
	}

	template <typename T>
	Point3<T> Permute(const Point3<T> &p, int x, int y, int z) {
		return Point3<T>(p[x], p[y], p[z]);
	}

	template <typename T, typename U>
	inline Normal3<T> operator*(U f, const Normal3<T> &n) {
		return Normal3<T>(f * n.x, f * n.y, f * n.z);
	}

	template <typename T>
	inline Normal3<T> Normalize(const Normal3<T> &n) {
		return n / n.Length();
	}

	template <typename T>
	inline Vec3<T>::Vec3(const Normal3<T> &n)
		: x(n.x), y(n.y), z(n.z) {
	}

	template <typename T>
	inline T Dot(const Normal3<T> &n1, const Vec3<T> &v2) {
		DCHECK(!n1.HasNaNs() && !v2.HasNaNs());
		return n1.x * v2.x + n1.y * v2.y + n1.z * v2.z;
	}

	template <typename T>
	inline T Dot(const Vec3<T> &v1, const Normal3<T> &n2) {
		return v1.x * n2.x + v1.y * n2.y + v1.z * n2.z;
	}

	template <typename T>
	inline T Dot(const Normal3<T> &n1, const Normal3<T> &n2) {
		return n1.x * n2.x + n1.y * n2.y + n1.z * n2.z;
	}

	template <typename T>
	inline T AbsDot(const Normal3<T> &n1, const Vec3<T> &v2) {
		return std::abs(n1.x * v2.x + n1.y * v2.y + n1.z * v2.z);
	}

	template <typename T>
	inline T AbsDot(const Vec3<T> &v1, const Normal3<T> &n2) {
		return std::abs(v1.x * n2.x + v1.y * n2.y + v1.z * n2.z);
	}

	template <typename T>
	inline T AbsDot(const Normal3<T> &n1, const Normal3<T> &n2) {
		return std::abs(n1.x * n2.x + n1.y * n2.y + n1.z * n2.z);
	}

	template <typename T>
	inline Normal3<T> Faceforward(const Normal3<T> &n, const Vec3<T> &v) {
		return (Dot(n, v) < 0.f) ? -n : n;
	}

	template <typename T>
	inline Normal3<T> Faceforward(const Normal3<T> &n, const Normal3<T> &n2) {
		return (Dot(n, n2) < 0.f) ? -n : n;
	}

	template <typename T>
	inline Vec3<T> Faceforward(const Vec3<T> &v, const Vec3<T> &v2) {
		return (Dot(v, v2) < 0.f) ? -v : v;
	}

	template <typename T>
	inline Vec3<T> Faceforward(const Vec3<T> &v, const Normal3<T> &n2) {
		return (Dot(v, n2) < 0.f) ? -v : v;
	}

	template <typename T>
	Normal3<T> Abs(const Normal3<T> &v) {
		return Normal3<T>(std::abs(v.x), std::abs(v.y), std::abs(v.z));
	}
	
}



#endif