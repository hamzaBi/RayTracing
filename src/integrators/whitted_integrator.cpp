#include "whitted_integrator.hpp"
#include <glm/gtx/string_cast.hpp>
#include <iostream>

namespace RT_ISICG
{
	Vec3f WhittedIntegrator::Li( const Scene & p_scene,
								 const Ray &   p_ray,
								 const float   p_tMin,
								 const float   p_tMax ) const
	{
		return trace( p_scene, p_ray, p_tMin, p_tMax, 0, false );
	}

	Vec3f WhittedIntegrator::trace( const Scene & p_scene,
									const Ray &	  p_ray,
									const float	  p_tMin,
									const float	  p_tMax,
									int			  p_bounces,
									const bool	  inObject ) const
	{
		HitRecord hitRecord;
		if ( p_scene.intersect( p_ray, p_tMin, p_tMax, hitRecord ) )
		{
			Vec3f li = BLACK;

			if ( p_bounces == _nbBounces ) return BLACK;

			BaseMaterial * material = hitRecord._object->getMaterial();
			if ( material->isMirror() )
			{
				Ray reflected( hitRecord._point, glm::reflect( p_ray.getDirection(), hitRecord._normal ) );
				reflected.offset( hitRecord._normal );
				li += trace( p_scene, reflected, p_tMin, p_tMax, p_bounces + 1, false );
			}
			else if ( material->isTransparent() )
			{
				float n1;
				float n2;
				if ( inObject ) { 
					n1 = material->getIOR();
					n2 = 1.f;
				}
				else
				{
					n1 = 1.f;
					n2 = material->getIOR();
				}

				float ior = n1 / n2;
				
				// reflexion color
				Vec3f reflectDir = glm::reflect( p_ray.getDirection(), hitRecord._normal );
				Ray	  reflectedRay( hitRecord._point, reflectDir );
				reflectedRay.offset( hitRecord._normal );
				Vec3f reflectedColor = trace( p_scene, reflectedRay, p_tMin, p_tMax, p_bounces + 1, !inObject );

				// refraction

				Vec3f refractedDir = glm::refract( p_ray.getDirection(), hitRecord._normal, ior );
				
				Vec3f refractedColor = BLACK;
				if (refractedDir != Vec3f(0.0f)) {
					Ray refractedRay( hitRecord._point, refractedDir );
					refractedRay.offset( -hitRecord._normal );
					refractedColor = trace( p_scene, refractedRay, p_tMin, p_tMax, p_bounces + 1, inObject );
				}

				//#define FRESNEL
				#define SCHLICK
				float kr = 0.0f;

				#ifdef FRESNEL
				float cosThetaI = glm::dot( p_ray.getDirection(), hitRecord._normal );
				float cosThetaO = glm::dot( refractedDir, hitRecord._normal );
				float num1		= n1 * cosThetaI - n2 * cosThetaO;
				float denom1	= n1 * cosThetaI + n2 * cosThetaO;
				float Rs		=pow((num1 / denom1), 2.0f);

				float num2	 = n1 * cosThetaO - n2 * cosThetaI;
				float denom2 = n1 * cosThetaO + n2 * cosThetaI;
				float Rp	 = pow((num2 / denom2), 2.0f);

				kr = 1.0f / 2.0f * ( Rs + Rp );
				#endif // FRESNEL

				#ifdef SCHLICK
				float cosTheta = glm::dot( -p_ray.getDirection(), hitRecord._normal );
				float R0	   = ( ( 1.f - n2 ) / ( 1.f + n2 ) ) * ( ( 1.f - n2 ) / ( 1.f + n2 ) );
				kr			   = R0 + ( 1 - R0 ) * pow( ( 1 - cosTheta ), 5.0f );
				#endif // SCHLICK
				li += ( kr * reflectedColor ) + ( 1.0f - kr ) * refractedColor;


			}
			else
			{
				for ( BaseLight * light : p_scene.getLights() )
				{
					Vec3f lightContrib = BLACK;
					int	  samples	   = light->isSurface() ? _nbLightSamples : 1;
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
			}
			return li;
		}
		else
		{
			return _backgroundColor;
		}
	}
} // namespace RT_ISICG