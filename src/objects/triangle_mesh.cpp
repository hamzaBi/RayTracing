#include "triangle_mesh.hpp"

namespace RT_ISICG
{
	void MeshTriangle::buildBVH()
	{
		//std::cout << "MeshTriangle::buildBVH => " << _triangles.size() << std::endl;
		_bvh.build( &_triangles, _aabb );
		
	}

	bool MeshTriangle::intersect( const Ray & p_ray,
								  const float p_tMin,
								  const float p_tMax,
								  HitRecord & p_hitRecord ) const
	{
		HitRecord tempHit;
		if (_bvh.intersect(p_ray, p_tMin, p_tMax, tempHit)) { 
			p_hitRecord = tempHit;
			p_hitRecord._object = this;
			return true;
		}
		return false;
	

		
	}

	bool MeshTriangle::intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax ) const
	{

		return _bvh.intersectAny( p_ray, p_tMin, p_tMax );
		//for ( size_t i = 0; i < _triangles.size(); i++ )
		//{
		//	float t;
		//	Vec2f uv;
		//	if ( _triangles[ i ].intersect( p_ray, t, uv ) )
		//	{
		//		if ( t >= p_tMin && t <= p_tMax ) return true; // No need to search for the nearest.
		//	}
		//}
		//return false;
	}



} // namespace RT_ISICG
