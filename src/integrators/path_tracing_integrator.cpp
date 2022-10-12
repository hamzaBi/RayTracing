#include "path_tracing_integrator.hpp"
#include <iostream>
#include "utils/random.hpp"
#include <math.h>
#include "defines.hpp"
#include <glm/gtx/string_cast.hpp>
namespace RT_ISICG
{
	Vec3f PathTracingIntegrator::Li( const Scene & p_scene,
								 const Ray &   p_ray,
								 const float   p_tMin,
								 const float   p_tMax ) const
	{
		return trace( p_scene, p_ray, p_tMin, p_tMax, 0, false );
	}

	
	const Vec3f PathTracingIntegrator::_getRandomRay( const Vec3f & p_hemisphere_dir ) const
	{
		float x1 = randomFloat();
		float x2 = randomFloat();
		float x	 = sqrt( x1 * ( 2 - x1 ) ) * cos( 2 * PIf * x2 ) + p_hemisphere_dir.x;
		float y	 = sqrt( x1 * ( 2 - x1 ) ) * sin( 2 * PIf * x2 ) + p_hemisphere_dir.y;
		float z	 = 1.0f - x1 + p_hemisphere_dir.z;

		return Vec3f( x, y, z );

		
	}

	
	Vec3f PathTracingIntegrator::trace( const Scene & p_scene,
										const Ray &	  p_ray,
										const float	  p_tMin,
										const float	  p_tMax,
										int			  p_bounces,
										const bool	  inObject ) const
	{
	
		HitRecord hitRecord;
		// if we reach our max bounces we return black
		if ( p_bounces == _maxBounds ) return BLACK;

		if ( p_scene.intersect( p_ray, p_tMin, p_tMax, hitRecord ) ) {
			// if there is an intersection
			// we need to shoot _nbsamples random reflected ray
			Vec3f li				   = BLACK;
			Vec3f indirectlightContrib = BLACK;
			Vec3f allLightsContrib = BLACK;

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
				if ( inObject )
				{
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
				if ( refractedDir != Vec3f( 0.0f ) )
				{
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
								float Rs		= pow( ( num1 / denom1 ), 2.0f );

								float num2	 = n1 * cosThetaO - n2 * cosThetaI;
								float denom2 = n1 * cosThetaO + n2 * cosThetaI;
								float Rp	 = pow( ( num2 / denom2 ), 2.0f );

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
				// calculating shadow contribution
				for ( BaseLight * light : p_scene.getLights() )
				{
					// for each light in the scene shoot a shadow ray

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
				for ( int i = 0; i < _nbSamples; i++ )
				{
					// generate a new random unit ray in hemisphere in call recursivly trace function to find the
					// inderectlightcontrib
					Vec3f rayDir = _getRandomRay( hitRecord._normal );
					Vec3f rayOr	 = hitRecord._point;
					Ray	  incommingRay( rayOr, rayDir );
					incommingRay.offset( hitRecord._normal );
					indirectlightContrib += trace( p_scene, incommingRay, p_tMin, p_tMax, p_bounces + 1, false );
				}
				indirectlightContrib /= 1.0f * _nbSamples;
				// add color to li
				// li += allLightsContrib; //+ indirectlightContrib;
				 li += indirectlightContrib;
			}
			return li;
		}
		else
		{
			return _backgroundColor;
		}
	
	}
} // namespace RT_ISICG
