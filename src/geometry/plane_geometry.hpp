#ifndef __RT_ISICG_PLANE_GEOMETRY__
#define __RT_ISICG_PLANE_GEOMETRY__

#include "base_geometry.hpp"

namespace RT_ISICG
{
	class PlaneGeometry : public BaseGeometry
	{
	  public:
		PlaneGeometry()		  = delete;
		virtual ~PlaneGeometry() = default;

		PlaneGeometry( const Vec3f & p_p0, const Vec3f & p_normal ) : 
			_p0( p_p0 ), 
			_normal( p_normal ), 
			_d( -glm::dot(getNormal(), getPZero() ) ) 
		{}


		bool intersect( const Ray & p_ray, float & p_t1, float & p_t2 ) const;

		inline const Vec3f & getPZero() const { return _p0; }
		inline const Vec3f & getNormal() const { return _normal; }

		inline Vec3f computeNormal( const Vec3f & p_point ) const
		{
			return _normal;
		}

	  private:
		Vec3f _p0;
		Vec3f _normal;
		float _d;
		
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_PLANE_GEOMETRY__
