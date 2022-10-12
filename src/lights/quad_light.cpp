#include "quad_light.hpp"
#include "utils/random.hpp"

namespace RT_ISICG
{
	 LightSample QuadLight::sample(const Vec3f & p_point) const { 
		// a-
		float randomU = randomFloat();
		float randomV = randomFloat();

		Vec3f randomPosition = _position + randomU * _u + randomV * _v;
		// b- rayon entre point observé et la position sur le quad
		Vec3f dir = randomPosition - p_point;
		// c-
		float distance = glm::length( dir );
		float cosND = glm::dot( _n, glm::normalize( dir ) );
		
		float p_pdf	   = ( 1.0f / _area)  *  (distance * distance ) / cosND;
		// d-
		Vec3f radiance = _color * _power / p_pdf;
		return LightSample( glm::normalize(dir), distance, radiance, p_pdf );
	 }

} // namespace RT_ISICG
