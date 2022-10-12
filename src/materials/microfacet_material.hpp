#ifndef __RT_ISICG_MICRO_FACET_MATERIAL__
#define __RT_ISICG_MICRO_FACET_MATERIAL__

#include "base_material.hpp"
#include "brdfs/oren_nayar_brdf.hpp"
#include "brdfs/cook_torrance_brdf.hpp"

namespace RT_ISICG
{
	class MicroFacetMaterial : public BaseMaterial
	{
	  public:
		MicroFacetMaterial( const std::string & p_name, const Vec3f & p_diffuse, const Vec3f & p_F0, const float & p_sigma, const float & p_metalness)
			: BaseMaterial( p_name ), _brdfOrenNayar( p_diffuse, p_sigma ), _brdfCookTorrance(p_sigma, p_F0), _metalness(p_metalness)
		{
		}

		virtual ~MicroFacetMaterial() = default;

		Vec3f shade( const Ray &		 p_ray,
					 const HitRecord &	 p_hitRecord,
					 const LightSample & p_lightSample ) const override
		{
			Vec3f specular = _brdfCookTorrance.evaluate( -p_ray.getDirection(), p_lightSample._direction, p_hitRecord._normal );
			Vec3f diffuse  = _brdfOrenNayar.evaluate( -p_ray.getDirection(), p_lightSample._direction, p_hitRecord._normal );
			return ( 1 - _metalness ) * diffuse + _metalness * specular; 
		}

		inline const Vec3f & getFlatColor() const override { return _brdfOrenNayar.getKd(); }

	  protected:
		OrenNayarBRDF _brdfOrenNayar;
		CookTorranceBRDF _brdfCookTorrance;
		float			 _metalness;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_LAMBERT_MATERIAL__