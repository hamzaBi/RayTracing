#ifndef __RT_ISICG_POINT_LIGHT__
#define __RT_ISICG_POINT_LIGHT__

#include "base_light.hpp"
#include "defines.hpp"

namespace RT_ISICG
{
	class PointLight : public BaseLight
	{
	  public:
		PointLight() = delete;
		PointLight( const Vec3f & p_color, const Vec3f & p_position,const float p_power = 1.0f)
			: BaseLight(p_color, p_power), _position( p_position )
		{
		}

		~PointLight() = default;

		inline const Vec3f getPosition() const { return _position; }

		virtual LightSample sample( const Vec3f & p_point ) const override;

	  private:
		Vec3f _position;
	};
} // namespace RT_ISICG

#endif