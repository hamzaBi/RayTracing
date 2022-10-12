#include "point_light.hpp"


namespace RT_ISICG
{
	 LightSample PointLight::sample(const Vec3f & p_point) const { 
		 Vec3f direction = getPosition() - p_point;
	
		 float distance	 = glm::length(direction);
		 
		 Vec3f radiance = _color * _power * 1.f/(distance*distance);

		 return LightSample( glm::normalize(direction), distance, radiance, 1.f );
	}

} // namespace RT_ISICG
