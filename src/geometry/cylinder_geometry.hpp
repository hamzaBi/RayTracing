#ifndef __RT_ISICG_CYLINDER_GEOMETRY__
#define __RT_ISICG_CYLINDER_GEOMETRY__

#include "base_geometry.hpp"

namespace RT_ISICG
{
	class CylinderGeometry : public BaseGeometry
	{
	  public:
		CylinderGeometry()		 = delete;
		virtual ~CylinderGeometry() = default;

		CylinderGeometry( const Vec3f & p_position, const float p_radius) : _position( p_position ), _radius( p_radius ) {}


		bool intersect( const Ray & p_ray, float & p_t1, float & p_t2 ) const;

		inline const Vec3f & getPosition() const { return _position; }
		inline const float & getRadius() const { return _radius; }

		inline Vec3f computeNormal( const Vec3f & p_point ) const
		{ 
			return Vec3f( 1.0f, .0f, 0.f );
		}

	  private:
		Vec3f _position;
		float _radius;
		
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_CYLINDER_GEOMETRY__
