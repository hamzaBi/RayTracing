#include "plane_geometry.hpp"

namespace RT_ISICG
{
	bool PlaneGeometry::intersect( const Ray & p_ray, float & p_t1, float & p_t2 ) const
	{
		float denom = glm::dot( p_ray.getDirection(), getNormal() );

		if ( denom > 1e-6 )
		{
			Vec3f p0o = getPZero() - p_ray.getOrigin();
			float t	  = -( glm::dot( p_ray.getOrigin(), _normal ) + _d ) / denom;
			p_t1	  = t;
			p_t2	  = t;
			return true;
		}

		return false;
	}

} // namespace RT_ISICG
