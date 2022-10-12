#ifndef __RT_ISICG_TRIANGLE__
#define __RT_ISICG_TRIANGLE__

#include "base_object.hpp"
#include "geometry/triangle_geometry.hpp"

namespace RT_ISICG
{
	class Triangle : public BaseObject
	{
	  public:
		Triangle()			= delete;
		virtual ~Triangle() = default;

		Triangle( const std::string & p_name, const Vec3f & p_v1, const Vec3f & p_v2, const Vec3f & p_v3 )
			: BaseObject( p_name ), _geometry( p_v1, p_v2, p_v3 )
		{
		}

		// Check for nearest intersection between p_tMin and p_tMax : if found fill p_hitRecord.
		virtual bool intersect( const Ray & p_ray,
								const float p_tMin,
								const float p_tMax,
								HitRecord & p_hitRecord ) const override;

		virtual bool intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax ) const override;

	  private:
		TriangleGeometry _geometry;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_SPHERE__
