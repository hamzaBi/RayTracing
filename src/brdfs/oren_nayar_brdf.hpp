#ifndef __RT_ISICG_BRDF_OREN_NAYAR__
#define __RT_ISICG_BRDF_OREN_NAYAR__
#include "defines.hpp"
#include "ray.hpp"
#include "hit_record.hpp"
#include "lights/light_sample.hpp"
#include <glm/gtx/string_cast.hpp>

namespace RT_ISICG
{
	class OrenNayarBRDF
	{
	  public:
		OrenNayarBRDF( const Vec3f & p_kd, float p_sigma ) : _kd( p_kd ), _sigma(p_sigma) {};
		// * INV_PIf : could be done in the constructor...
		inline Vec3f evaluate( const Vec3f & Wo, const Vec3f & Wi, const Vec3f & n) const
		{
			float cosThetao = glm::dot( -Wo, n );
			float cosThetai = glm::dot( Wi, n );

			float thetao = acos( cosThetao );
			float thetai = acos( cosThetai );

			Vec3f WiPhi = glm::normalize(Wi - n * cosThetai);
			Vec3f WoPhi = glm::normalize(-Wo - n * cosThetao);

			float cosPhiDiff = 0.0f;
			cosPhiDiff = glm::dot( WoPhi, WiPhi );

			float sigma2 = _sigma * _sigma;
			float A		 = 1.0f - ( (0.5f * sigma2)  / ( sigma2 + 0.33f ) );
			float B		 = (0.45f * sigma2)/ ( sigma2 + 0.09f );

			float alpha = glm::max( thetai, thetao );
			float beta	= glm::min( thetai, thetao );
			
			B = ( cosPhiDiff >= 0 ) ? B * cosPhiDiff * ( alpha ) * tan( beta ) : 0;
			 
			return _kd * INV_PIf * ( A + B);

			 
		}
		inline const Vec3f & getKd() const { return _kd; }

	  private:
		Vec3f _kd = WHITE;
		float _sigma;
	};
} // namespace RT_ISICG
#endif // __RT_ISICG_BRDF_OREN_NAYAR__