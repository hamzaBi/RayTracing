#include "ray_cast_integrator.hpp"
#include <iostream>
namespace RT_ISICG
{
	Vec3f RayCastIntegrator::Li( const Scene & p_scene,
								 const Ray &   p_ray,
								 const float   p_tMin,
								 const float   p_tMax ) const
	{
		HitRecord hitRecord;
		
		if ( p_scene.intersect( p_ray, p_tMin, p_tMax, hitRecord ) )
		{
			/// TODO ! cos theta...
			
			
			float cosTheta = glm::dot(-p_ray.getDirection(), hitRecord._normal);
			
			return  hitRecord._object->getMaterial()->getFlatColor() * glm::max(0.0f,cosTheta);
		}
		else
		{
			return _backgroundColor;
		}
	}
} // namespace RT_ISICG
