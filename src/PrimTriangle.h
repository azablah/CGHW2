// Triangle Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "Prim.h"

/**
 * @brief Triangle Geaometrical Primitive class
 */
class CPrimTriangle : public CPrim
{
public:
	/**
	 * @brief Constructor
	 * @param a Position of the first vertex
	 * @param b Position of the second vertex
	 * @param c Position of the third vertex
	 */
	CPrimTriangle(Vec3f a, Vec3f b, Vec3f c)
		: CPrim()
		, m_a(a)
		, m_b(b)
		, m_c(c)
  	{}
	virtual ~CPrimTriangle(void) = default;
	
	virtual bool Intersect(Ray& ray) override {

		const Vec3f e1 = m_b - m_a;
		const Vec3f e2 = m_c - m_a;			
		const Vec3f pvector = ray.dir.cross(e2);
		const float determinant = e1.dot(pvector);
		if (fabs(determinant) < Epsilon){
			 return false;
		}
		const float inv_determinant = 1.0f / determinant;		
		const Vec3f tvector = ray.org - m_a;
		float lambda = tvector.dot(pvector);
		lambda *= inv_determinant;
		if (lambda < 0.0f || lambda > 1.0f) {
			return false;
		}		
		const Vec3f qvector = tvector.cross(e1);
		float mu = ray.dir.dot(qvector);
		mu *= inv_determinant;
		if (mu < 0.0f || mu + lambda > 1.0f) {
			return false;
		}
		float func = e2.dot(qvector);
		func *= inv_determinant;
		if (ray.t <= func || func <  1E-4  ) {
			return false;	
		}

		ray.t = f;
		return true;
	}

	
private:
	Vec3f m_a;	///< Position of the first vertex
	Vec3f m_b;	///< Position of the second vertex
	Vec3f m_c;	///< Position of the third vertex
};
