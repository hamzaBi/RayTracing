#ifndef __RT_ISICG_QUAD_LIGHT__
#define __RT_ISICG_QUAD_LIGHT__

#include "base_light.hpp"
#include "defines.hpp"

namespace RT_ISICG
{
	class QuadLight : public BaseLight
	{
	  public:
		QuadLight() = delete;
		QuadLight(Vec3f p_position, Vec3f p_u, Vec3f p_v, Vec3f p_color, float p_power)
			: BaseLight(p_color, p_power, true), 
			_position( p_position ), 
			_u(p_u), 
			_v(p_v), 
			_area(glm::length(p_u) * glm::length(p_v)), 
			_n(glm::normalize(glm::cross(_u, _v)))
		{
		}

		~QuadLight() = default;

		inline const Vec3f getPosition() const { return _position; }
		inline const Vec3f getU() const { return _u; }
		inline const Vec3f getV() const { return _v; }
		inline const Vec3f  getNormal() const { return _n; }
		inline const float getArea() const { return _area; }

		virtual LightSample sample( const Vec3f & p_point ) const override;

	  private:
		Vec3f _position;
		Vec3f _u;
		Vec3f _v;
		Vec3f _n;
		float _area;
	};
} // namespace RT_ISICG

#endif