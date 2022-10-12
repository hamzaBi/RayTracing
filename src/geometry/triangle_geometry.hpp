#ifndef __RT_ISICG_TRIANGLE_GEOMETRY__
#define __RT_ISICG_TRIANGLE_GEOMETRY__

#include "base_geometry.hpp"
#include <assert.h>

namespace RT_ISICG
{
	class TriangleGeometry : public BaseGeometry
	{
	  public:
		TriangleGeometry()			= delete;
		virtual ~TriangleGeometry() = default;

		TriangleGeometry( const Vec3f & p_v1, const Vec3f & p_v2, const Vec3f & p_v3 )
			: _v1( p_v1 ), _v2( p_v2 ), _v3( p_v3 ), _u( -1.f ), _v( -1.f )
		{
		}

		inline const Vec3f getVertexAt( int index )
		{
			assert( index >= 0 && index < 3 );

			if ( index == 0 )
				return _v1;
			else if ( index == 1 )
				return _v2;
			else if ( index == 2 )
				return _v3;
		}

		void setUVCoord( float, float );

		float getU() { return _u; }
		float getV() { return _v; }

		bool intersect( const Ray & p_ray, float & p_t1, float & p_t2 ) const;

		inline Vec3f computeNormal() const
		{
			Vec3f edge1 = _v2 - _v1;
			Vec3f edge2 = _v3 - _v1;
			return glm::normalize( glm::cross( edge2, edge1 ) );
		}

	  private:
		Vec3f _v1;
		Vec3f _v2;
		Vec3f _v3;
		float _u;
		float _v;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_SPHERE_GEOMETRY__
