#ifndef __RT_ISICG_TRIANGLE_MESH_GEOMETRY__
#define __RT_ISICG_TRIANGLE_MESH_GEOMETRY__

#include "base_geometry.hpp"
#include <vector>

namespace RT_ISICG
{
	class MeshTriangle;

	class TriangleMeshGeometry : public BaseGeometry
	{
	  public:
		TriangleMeshGeometry()			= delete;
		virtual ~TriangleMeshGeometry() = default;

		TriangleMeshGeometry( const uint p_v0, const uint p_v1, const uint p_v2, MeshTriangle * p_refMesh );

		bool  intersect( const Ray & p_ray, float & p_t, Vec2f & uv ) const;
		Vec3f computeNormal( const Vec2f & uv ) const;

		inline const Vec3f & getFaceNormal() const { return _faceNormal; }

		const Vec3f &		 getVecAt( uint i ) const;
		const float			 centroid( int );
		const Vec2f &		 getUVAt( uint i ) const;
		
		bool operator==( const TriangleMeshGeometry & other );

		// bool operator<( const TriangleMeshGeometry & other ) { return centroid() < other.centroid(); }

	  private:
		MeshTriangle * _refMesh;
		union
		{
			struct
			{
				uint _v0, _v1, _v2;
			};
			uint _v[ 3 ] = { 0, 0, 0 };
		};

		Vec3f _faceNormal;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_TRIANGLE_GEOMETRY__
