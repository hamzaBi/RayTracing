#include "aabb.hpp"

namespace RT_ISICG
{
	/*void AABB::extend( const Vec3f & p_v )
	{
		Vec3f min = getMin();
		Vec3f max = getMax();
		min.x	  = ( p_v.x < min.x ) ? p_v.x : min.x;
		min.x	  = ( p_v.y < min.y ) ? p_v.y : min.y;
		min.x	  = ( p_v.z < min.z ) ? p_v.z : min.z;
		max.x	  = ( p_v.x > max.x ) ? p_v.x : max.x;
		max.y	  = ( p_v.y > max.y ) ? p_v.y : max.y;
		max.x	  = ( p_v.z > max.z ) ? p_v.z : max.z;
		_min	  = min;
		_max	  = max;
	}*/

	bool AABB::intersect( const Ray & p_ray, const float p_tMin, const float p_tMax ) const
	{
		const Vec3f & o = p_ray.getOrigin();
		const Vec3f & d = p_ray.getDirection();

		float temp;

		float tMin = ( _min.x - o.x ) / d.x;
		float tMax = ( _max.x - o.x ) / d.x;
		if ( tMin > tMax )
		{
			temp = tMax;
			tMax = tMin;
			tMin = temp;
		}

		float tyMin = ( _min.y - o.y ) / d.y;
		float tyMax = ( _max.y - o.y ) / d.y;

		if ( tyMin > tyMax )
		{
			temp  = tyMax;
			tyMax = tyMin;
			tyMin = temp;
		}

		if ( ( tMin > tyMax ) || ( tyMin > tMax ) ) return false;

		float tzMin = ( _min.z - o.z ) / d.z;
		float tzMax = ( _max.z - o.z ) / d.z;

		if ( tzMin > tzMax )
		{
			temp  = tzMax;
			tzMax = tzMin;
			tzMin = temp;
		}

		if ( ( tMin > tzMax ) || ( tzMin > tMax ) ) return false;

		if ( tzMin > tMin ) tMin = tzMin;
		if ( tzMax < tMax ) tMax = tzMax;
		if ( tMin > p_tMax ) { return false; }					// first intersection too far
		if ( tMin < p_tMin ) { tMin = tMax; }					// first intersection too near, check second one
		if ( tMin < p_tMin || tMin > p_tMax ) { return false; } // not in range
		return true;
	}
} // namespace RT_ISICG
