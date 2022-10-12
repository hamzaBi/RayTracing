#ifndef __RT_ISICG_BRDF_COOK_TORRANCE__
#define __RT_ISICG_BRDF_COOK_TORRANCE__
#include "defines.hpp"
#include "ray.hpp"
#include "hit_record.hpp"
#include "lights/light_sample.hpp"
#include <glm/gtx/string_cast.hpp>

namespace RT_ISICG
{
	class CookTorranceBRDF
	{
	  public:
		CookTorranceBRDF(float p_sigma, const Vec3f & p_F0 ) : _F0(p_F0), _alpha(p_sigma * p_sigma) {};
		// * INV_PIf : could be done in the constructor...
		inline Vec3f evaluate( const Vec3f & Wo, const Vec3f & Wi, const Vec3f & n) const
		{
			Vec3f h = glm::normalize( Wo + Wi );
			float d = D( h, n );
			float g = G( Wi, Wo, n );
			Vec3f f = F( Wo, h );
			Vec3f num	= d * g * f;
			float denom = 4.0f * glm::max( 0.0f, glm::dot( Wo, n ) ) * glm::max( 0.0f, glm::dot( Wi, n ) );

			return num / denom;
		}

	  private:
		inline float D( Vec3f & h, const Vec3f & n) const 
		{ 
			

			float noh2 = glm::dot( n, h ) * glm::dot( n, h );
			float noh4 = noh2 * noh2;
			float _alpha2 = _alpha * _alpha;
			float p		  = ( (noh2 - 1.0f)/(_alpha2*noh2 ));
			return (1.0f/(PIf*_alpha2*noh4) * std::exp(p));

			/*float alpha2 = _alpha * _alpha;
			float NdotH2 = pow( glm::max( 0.0f, glm::dot( n, h ) ), 2.0f );
			float denom	 = PIf * pow( ( NdotH2 * ( alpha2 - 1.0f ) + 1.0f ), 2.0f );
			return alpha2 / denom;*/
		}

		inline float G( const Vec3f & Wi, const Vec3f & Wo, const Vec3f & n ) const
		{ 
			return G1( glm::max( 0.0f, glm::dot( n, Wo ) ) ) * G1( glm::max( 0.0f, glm::dot( n, Wi ) ) );
		}

		inline float G1( float  x ) const
		{ 
			float k = ( sqrt(_alpha) + 1.f ) * ( sqrt(_alpha) + 1.0f )/8.f;
			return x / ( x * ( 1.f - k ) + k );
		}

		inline Vec3f F(const Vec3f& Wo, Vec3f& h) const
		{ 
			return _F0 + ( 1.0f - _F0 ) * pow( ( 1.f - glm::max( 0.0f, glm::dot( h, Wo ) ) ), 5.f ); 
		}

	  private:
		float _alpha;
		Vec3f _F0;
	};
} // namespace RT_ISICG
#endif // __RT_ISICG_BRDF_OREN_NAYAR__