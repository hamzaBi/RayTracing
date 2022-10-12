#ifndef __RT_ISICG_PLASTIC_MATERIAL__
#define __RT_ISICG_PLASTIC_MATERIAL__

#include "base_material.hpp"
#include "brdfs/phong_brdf.hpp"
#include "brdfs/lambert_brdf.hpp"

namespace RT_ISICG
{
	class PlasticMaterial : public BaseMaterial
	{
	  public:
		PlasticMaterial( const std::string & p_name, const Vec3f & p_diffuse, const Vec3f & p_ks, const int & p_s,const float & p_specularity )
			: BaseMaterial( p_name ), _brdfPhong( p_diffuse, p_ks, p_s ), _brdfLambert( p_diffuse ), _specularity(p_specularity)
		{
		}

		virtual ~PlasticMaterial() = default;

		Vec3f shade( const Ray &		 p_ray,
					 const HitRecord &	 p_hitRecord,
					 const LightSample & p_lightSample ) const override
		{
			Vec3f phong =  _brdfPhong.evaluate(-p_ray.getDirection(), p_lightSample._direction, p_hitRecord._normal);
			Vec3f lambert = _brdfLambert.evaluate();
			return _specularity * phong + ( 1.0f - _specularity ) * lambert;
		}

		inline const Vec3f & getFlatColor() const override { return _brdfPhong.getKd(); }

	  protected:
		PhongBRDF _brdfPhong;
		LambertBRDF _brdfLambert;
		float		_specularity;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_LAMBERT_MATERIAL__