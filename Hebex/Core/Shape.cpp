#include "Shape.h"
#include "Intersection.h"
#include "Geometry.h"
namespace Hebex
{
	Shape::Shape(const Transform *o2w, const Transform *w2o) :
		ObjectToWorld(o2w), WorldToObject(w2o), shapeId(nextShapeId++) {

	}

	Shape::~Shape() { }

	uint32_t Shape::nextShapeId = 1;

	BBox Shape::WorldBound() const {
		return (*ObjectToWorld)(ObjectBound());
	}

	bool Shape::Intersectable() const {
		return true;
	}

	void Shape::Refine(std::vector<std::shared_ptr<Shape> > &refined) const {

	}

	float Shape::Area() const {
		return 0.f;
	}

	float Shape::Pdf(const Point3f &p, const Vec3f &wi) const {
		Intersection isect;
		Ray ray(p, wi, 1e-3f);
		if (!Intersect(ray, isect)) return 0.f;

		float pdf = DistanceSquared(p, isect.mPosition) / (AbsDot(isect.mNormal, -wi) * Area());

		if (isinf(pdf)) pdf = 0.f;
		return pdf;
	}

}