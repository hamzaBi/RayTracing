#include "sphere_geometry.hpp"

namespace RT_ISICG
{
	bool SphereGeometry::intersect( const Ray & p_ray, float & p_t1, float & p_t2 ) const
	{
		/// TODO !

		Vec3f oc = p_ray.getOrigin() - getCenter();
		float r	 = getRadius();
		float b	 = -dot( oc, p_ray.getDirection() );
		float c2 = dot( oc, oc ) - r * r;
		float d	 = b * b - c2;
		if ( d < 0.0f ) return false;
		float s = sqrt( d );
		p_t1	= b - s;
		p_t2	= b + s;
		return true;
	}

} // namespace RT_ISICG
