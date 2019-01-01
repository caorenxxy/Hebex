#ifndef TRANSFORM_H
#define TRANSFROM_H
#include "Geometry.h"
#include "Ray.h"
#include "BBox.h"
#include "Hebex.h"

namespace Hebex
{
	// Matrix4x4 Declarations
	struct Matrix4x4 {
		// Matrix4x4 Public Methods
		Matrix4x4() {
			m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.f;
			m[0][1] = m[0][2] = m[0][3] = m[1][0] =
				m[1][2] = m[1][3] = m[2][0] = m[2][1] = m[2][3] =
				m[3][0] = m[3][1] = m[3][2] = 0.f;
		}
		Matrix4x4(float mat[4][4]);

		Matrix4x4(float t00, float t01, float t02, float t03,
			float t10, float t11, float t12, float t13,
			float t20, float t21, float t22, float t23,
			float t30, float t31, float t32, float t33);

		bool operator==(const Matrix4x4 &m2) const {
			for (int i = 0; i < 4; ++i)
				for (int j = 0; j < 4; ++j)
					if (m[i][j] != m2.m[i][j]) return false;
			return true;
		}

		bool operator!=(const Matrix4x4 &m2) const {
			for (int i = 0; i < 4; ++i)
				for (int j = 0; j < 4; ++j)
					if (m[i][j] != m2.m[i][j]) return true;
			return false;
		}

		friend Matrix4x4 Transpose(const Matrix4x4 &);

		static Matrix4x4 Mul(const Matrix4x4 &m1, const Matrix4x4 &m2) {
			Matrix4x4 r;
			for (int i = 0; i < 4; ++i)
				for (int j = 0; j < 4; ++j)
					r.m[i][j] = m1.m[i][0] * m2.m[0][j] +
					m1.m[i][1] * m2.m[1][j] +
					m1.m[i][2] * m2.m[2][j] +
					m1.m[i][3] * m2.m[3][j];
			return r;
		}

		static Matrix4x4 Identity() {
			return Matrix4x4();
		}

		friend Matrix4x4 Inverse(const Matrix4x4 &);

		friend std::ostream &operator<<(std::ostream &os, const Matrix4x4 &mat) {
			os << "[" << std::endl;
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 4; ++j) {
					os << mat.m[i][j] << " ";
				}
				os << std::endl;
			}
			os << "]" << std::endl;
			return os;
		}

		float m[4][4];
	};


	class Transform {
	public:
		// Transform Public Methods
		Transform() { }

		Transform(const float mat[4][4]) {
			m = Matrix4x4(mat[0][0], mat[0][1], mat[0][2], mat[0][3],
				mat[1][0], mat[1][1], mat[1][2], mat[1][3],
				mat[2][0], mat[2][1], mat[2][2], mat[2][3],
				mat[3][0], mat[3][1], mat[3][2], mat[3][3]);
			mInv = Inverse(m);
		}

		Transform(const Matrix4x4 &mat)
			: m(mat), mInv(Inverse(mat)) {
		}

		Transform(const Matrix4x4 &mat, const Matrix4x4 &minv)
			: m(mat), mInv(minv) {
		}

		friend Transform Inverse(const Transform &t) {
			return Transform(t.mInv, t.m);
		}

		friend Transform Transpose(const Transform &t) {
			return Transform(Transpose(t.m), Transpose(t.mInv));
		}

		friend Transform TransformNormal(const Transform &t) {
			return Transpose(Inverse(t));
		}

		bool operator==(const Transform &t) const {
			return t.m == m && t.mInv == mInv;
		}

		bool operator!=(const Transform &t) const {
			return t.m != m || t.mInv != mInv;
		}

		bool operator<(const Transform &t2) const {
			for (uint32_t i = 0; i < 4; ++i)
				for (uint32_t j = 0; j < 4; ++j) {
					if (m.m[i][j] < t2.m.m[i][j]) return true;
					if (m.m[i][j] > t2.m.m[i][j]) return false;
				}
			return false;
		}

		bool IsIdentity() const {
			return (m.m[0][0] == 1.f && m.m[0][1] == 0.f &&
				m.m[0][2] == 0.f && m.m[0][3] == 0.f &&
				m.m[1][0] == 0.f && m.m[1][1] == 1.f &&
				m.m[1][2] == 0.f && m.m[1][3] == 0.f &&
				m.m[2][0] == 0.f && m.m[2][1] == 0.f &&
				m.m[2][2] == 1.f && m.m[2][3] == 0.f &&
				m.m[3][0] == 0.f && m.m[3][1] == 0.f &&
				m.m[3][2] == 0.f && m.m[3][3] == 1.f);
		}

		const Matrix4x4 &GetMatrix() const { return m; }

		const Matrix4x4 &GetInverseMatrix() const { return mInv; }

		inline Point3f operator()(const Point3f &pt) const;

		inline void operator()(const Point3f &pt, Point3f *ptrans) const;

		inline Vec3f operator()(const Vec3f &v) const;

		inline void operator()(const Vec3f &v, Vec3f *vt) const;

		inline Normal3f operator()(const Normal3f &) const;

		inline void operator()(const Normal3f &, Normal3f *nt) const;

		inline Ray operator()(const Ray &r) const;

		inline void operator()(const Ray &r, Ray *rt) const;

		inline RayDifferential operator()(const RayDifferential &r) const;

		inline void operator()(const RayDifferential &r, RayDifferential *rt) const;

		BBox operator()(const BBox &b) const;

		Transform operator*(const Transform &t2) const;

		bool SwapsHandedness() const;

		friend std::ostream &operator<<(std::ostream &os, const Transform &t) {
			os << "mat:" << std::endl << t.m;
			os << "inv mat:" << std::endl << t.mInv;
			return os;
		}
	private:
		// Transform Private Data
		Matrix4x4 m, mInv;
	};

	Transform Translate(const Vec3f &delta);
	Transform Scale(float x, float y, float z);
	Transform RotateX(float angle);
	Transform RotateY(float angle);
	Transform RotateZ(float angle);
	Transform Rotate(float angle, const Vec3f &axis);
	Transform LookAt(const Point3f &pos, const Point3f &look, const Vec3f &up);
	bool SolveLinearSystem2x2(const float A[2][2], const float B[2], float *x0, float *x1);
	Transform Orthographic(float znear, float zfar);
	Transform Perspective(float fov, float znear, float zfar);

	// Transform Inline Functions
	inline Point3f Transform::operator()(const Point3f &pt) const {
		float x = pt.x, y = pt.y, z = pt.z;
		float xp = m.m[0][0] * x + m.m[0][1] * y + m.m[0][2] * z + m.m[0][3];
		float yp = m.m[1][0] * x + m.m[1][1] * y + m.m[1][2] * z + m.m[1][3];
		float zp = m.m[2][0] * x + m.m[2][1] * y + m.m[2][2] * z + m.m[2][3];
		float wp = m.m[3][0] * x + m.m[3][1] * y + m.m[3][2] * z + m.m[3][3];
		if (wp == 1.) return Point3f(xp, yp, zp);
		else          return Point3f(xp, yp, zp) / wp;
	}


	inline void Transform::operator()(const Point3f &pt, Point3f *ptrans) const {
		float x = pt.x, y = pt.y, z = pt.z;
		ptrans->x = m.m[0][0] * x + m.m[0][1] * y + m.m[0][2] * z + m.m[0][3];
		ptrans->y = m.m[1][0] * x + m.m[1][1] * y + m.m[1][2] * z + m.m[1][3];
		ptrans->z = m.m[2][0] * x + m.m[2][1] * y + m.m[2][2] * z + m.m[2][3];
		float w = m.m[3][0] * x + m.m[3][1] * y + m.m[3][2] * z + m.m[3][3];
		if (w != 1.) *ptrans /= w;
	}


	inline Vec3f Transform::operator()(const Vec3f &v) const {
		float x = v.x, y = v.y, z = v.z;
		return Vec3f(m.m[0][0] * x + m.m[0][1] * y + m.m[0][2] * z,
			m.m[1][0] * x + m.m[1][1] * y + m.m[1][2] * z,
			m.m[2][0] * x + m.m[2][1] * y + m.m[2][2] * z);
	}


	inline void Transform::operator()(const Vec3f &v,
		Vec3f *vt) const {
		float x = v.x, y = v.y, z = v.z;
		vt->x = m.m[0][0] * x + m.m[0][1] * y + m.m[0][2] * z;
		vt->y = m.m[1][0] * x + m.m[1][1] * y + m.m[1][2] * z;
		vt->z = m.m[2][0] * x + m.m[2][1] * y + m.m[2][2] * z;
	}


	inline Normal3f Transform::operator()(const Normal3f &n) const {
		float x = n.x, y = n.y, z = n.z;
		return Normal3f(mInv.m[0][0] * x + mInv.m[1][0] * y + mInv.m[2][0] * z,
			mInv.m[0][1] * x + mInv.m[1][1] * y + mInv.m[2][1] * z,
			mInv.m[0][2] * x + mInv.m[1][2] * y + mInv.m[2][2] * z);
	}


	inline void Transform::operator()(const Normal3f &n,
		Normal3f *nt) const {
		float x = n.x, y = n.y, z = n.z;
		nt->x = mInv.m[0][0] * x + mInv.m[1][0] * y +
			mInv.m[2][0] * z;
		nt->y = mInv.m[0][1] * x + mInv.m[1][1] * y +
			mInv.m[2][1] * z;
		nt->z = mInv.m[0][2] * x + mInv.m[1][2] * y +
			mInv.m[2][2] * z;
	}


	inline Ray Transform::operator()(const Ray &r) const {
		Ray ret = r;
		(*this)(ret.mOrigin, &ret.mOrigin);
		(*this)(ret.mDirection, &ret.mDirection);
		return ret;
	}

	inline void Transform::operator()(const Ray &r, Ray *rt) const {
		(*this)(r.mOrigin, &rt->mOrigin);
		(*this)(r.mDirection, &rt->mDirection);
		if (rt != &r) {
			rt->tMin = r.tMin;
			rt->tMax = r.tMax;
		}
	}

	inline void Transform::operator()(const RayDifferential &r, RayDifferential *rt) const {
		(*this)(Ray(r), (Ray*)(rt));
		rt->hasDifferentials = r.hasDifferentials;
		(*this)(r.rxOrigin, &rt->rxOrigin);
		(*this)(r.ryOrigin, &rt->ryOrigin);
		(*this)(r.rxDirection, &rt->rxDirection);
		(*this)(r.ryDirection, &rt->ryDirection);
	}


	inline RayDifferential Transform::operator()(const RayDifferential &r) const {
		RayDifferential ret;
		(*this)(Ray(r), (Ray*)(&ret));
		ret.hasDifferentials = r.hasDifferentials;
		(*this)(r.rxOrigin, &ret.rxOrigin);
		(*this)(r.ryOrigin, &ret.ryOrigin);
		(*this)(r.rxDirection, &ret.rxDirection);
		(*this)(r.ryDirection, &ret.ryDirection);
		return ret;
	}

}

#endif
