#include "triangle_geometry.hpp"

namespace RT_ISICG
{
	void TriangleGeometry::setUVCoord( float u, float v )
	{
		_u = u;
		_v = v;
	}

	bool TriangleGeometry::intersect( const Ray & p_ray, float & p_t1, float & p_t2 ) const
	{
		const double EPSILON = 1e-6;
		Vec3f		 edge1	 = _v2 - _v1;
		Vec3f		 edge2	 = _v3 - _v1;

		Vec3f pvec = glm::cross( p_ray.getDirection(), edge2 );
		float det  = glm::dot( edge1, pvec );

		if ( abs( det ) < EPSILON ) return false;

		float invDet = 1.0f / det;
		Vec3f tvec	 = p_ray.getOrigin() - _v1;

		float u = glm::dot( tvec, pvec ) * invDet;

		if ( u < 0.f || u > 1.f ) return false;

		Vec3f qvec = glm::cross( tvec, edge1 );
		float v	   = glm::dot( p_ray.getDirection(), qvec ) * invDet;
		if ( v < .0f || u + v > 1.f ) return false;

		float t = glm::dot( edge2, qvec ) * invDet;

		p_t1 = t;
		p_t2 = t;

		return true;
	}

} // namespace RT_ISICG
