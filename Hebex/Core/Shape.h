#ifndef SHAPE_H
#define SHAPE_H

#include "../ForwardDecl.h"
#include "Hebex.h"
#include "Geometry.h"

namespace Hebex
{
	class Shape {
	public:
		//Shape Interface
		Shape(const Transform *o2w, const Transform *w2o);

		virtual ~Shape();

		virtual BBox ObjectBound() const = 0;
		
		virtual BBox WorldBound() const;

		virtual bool Intersectable() const;

		virtual void Refine(std::vector<std::shared_ptr<Shape> > &refined) const;
		
		virtual bool Intersect(const Ray &ray, Intersection *isect) const = 0;
		
		virtual bool IntersectP(const Ray &ray) const = 0;
		
		virtual float Area() const = 0;

		virtual Point3f Sample(const Point2f &u, Vec3f *normal) const {
			return Point3f();
		}

		virtual Point3f Sample(const Point3f &p, const Point2f &u, Vec3f *normal) const {
			return Sample(u, normal);
		}

		virtual float Pdf(const Point3f &p, const Vec3f &wi) const;


		const Transform *ObjectToWorld, *WorldToObject;
		const uint32_t shapeId;
		static uint32_t nextShapeId;

	};
}


#endif
