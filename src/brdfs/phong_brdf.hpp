#ifndef __RT_ISICG_BRDF_PHONG__
#define __RT_ISICG_BRDF_PHONG__
#include "defines.hpp"
namespace RT_ISICG
{
	class PhongBRDF
	{
	  public:
		PhongBRDF( const Vec3f & p_kd, const Vec3f & p_ks, int p_s ) : _kd( p_kd ), _ks(p_ks), _s(p_s) {};
		// * INV_PIf : could be done in the constructor...
		inline Vec3f evaluate(const Vec3f & Wo, const Vec3f & Wi, const Vec3f & n) const { 

			Vec3f h = glm::normalize( Wo + Wi );
		
			Vec3f Wr = glm::normalize(glm::reflect(-Wi, n )); 

			float cosAlpha = glm::max(0.0f, glm::dot( Wo, Wr ));
			Vec3f result =  (float)pow(cosAlpha, _s) * _ks; 
			return result;
		}
		inline const Vec3f & getKd() const { return _kd; }
	  private:
		Vec3f _kd = WHITE;
		Vec3f _ks;
		int	  _s;
	};
} // namespace RT_ISICG
#endif // __RT_ISICG_BRDF_PHONG__