#include "direct_light_integrator.hpp"
#include <glm/gtx/string_cast.hpp>
#include <iostream>

namespace RT_ISICG
{
	Vec3f DirectLightIntegrator::Li( const Scene & p_scene,
									 const Ray &   p_ray,
									 const float   p_tMin,
									 const float   p_tMax ) const
	{
		HitRecord hitRecord;

		if ( p_scene.intersect( p_ray, p_tMin, p_tMax, hitRecord ) )
		{
			Vec3f li( 0.f );
			for ( BaseLight * light : p_scene.getLights() )
			{
				Vec3f lightContrib = BLACK;

				int samples = light->isSurface() ? _nbLightSamples : 1;

				for ( int i = 0; i < samples; i++ )
				{
					const LightSample light_sample		   = light->sample( hitRecord._point );
					Vec3f			  shadow_ray_origin	   = hitRecord._point;
					Vec3f			  shadow_ray_direction = light_sample._direction;
					Ray				  shadowRay( shadow_ray_origin, shadow_ray_direction );
					shadowRay.offset( hitRecord._normal );
					if ( !p_scene.intersectAny( shadowRay, p_tMin, light_sample._distance ) )
					{
						lightContrib += hitRecord._object->getMaterial()->shade( p_ray, hitRecord, light_sample )
										* glm::dot( light_sample._direction, hitRecord._normal )
										* light_sample._radiance;
					}
				}
				lightContrib /= (float)samples;
				li += lightContrib;
			}
			return li;
		}
		else
		{
			return _backgroundColor;
		}
	}
} // namespace RT_ISICG
