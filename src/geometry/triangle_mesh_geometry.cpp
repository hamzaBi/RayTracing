#include "triangle_mesh_geometry.hpp"
#include "objects/triangle_mesh.hpp"

namespace RT_ISICG
{
	TriangleMeshGeometry::TriangleMeshGeometry( const uint	   p_v0,
												const uint	   p_v1,
												const uint	   p_v2,
												MeshTriangle * p_refMesh )
		: _v0( p_v0 ), _v1( p_v1 ), _v2( p_v2 ), _refMesh( p_refMesh )
	{
		_faceNormal = glm::normalize( glm::cross( _refMesh->_vertices[ p_v1 ] - _refMesh->_vertices[ p_v0 ],
												  _refMesh->_vertices[ p_v2 ] - _refMesh->_vertices[ p_v0 ] ) );
	}


	bool TriangleMeshGeometry::intersect( const Ray & p_ray, float & p_t, Vec2f & uv ) const
	{
		const Vec3f & o	 = p_ray.getOrigin();
		const Vec3f & d	 = p_ray.getDirection();
		const Vec3f & v0 = _refMesh->_vertices[ _v0 ];
		const Vec3f & v1 = _refMesh->_vertices[ _v1 ];
		const Vec3f & v2 = _refMesh->_vertices[ _v2 ];

		const float EPSILON = 1e-6;

		Vec3f edge1 = v1 - v0;
		Vec3f edge2 = v2 - v0;

		Vec3f pvec = glm::cross( d, edge2 );

		float det = glm::dot( edge1, pvec );

		if ( det > -EPSILON && det < EPSILON ) return false;

		float inv_det = 1.0f / det;
		Vec3f tvec	  = o - v0;

		float u = glm::dot( tvec, pvec ) * inv_det;

		if ( u < 0.0f || u > 1.0f ) return false;

		Vec3f qvec = glm::cross( tvec, edge1 );
		float v	   = glm::dot( d, qvec ) * inv_det;

		if ( v < 0.f || u + v > 1.0f ) return false;

		float t = glm::dot( edge2, qvec ) * inv_det;

		p_t = t;

		uv = Vec2f( u, v );
		return true;
	}

	Vec3f TriangleMeshGeometry::computeNormal( const Vec2f & uv ) const
	{
		const float & u	 = uv.x;
		const float & v	 = uv.y;
		const Vec3f & n0 = _refMesh->_normals[ _v0 ];
		const Vec3f & n1 = _refMesh->_normals[ _v1 ];
		const Vec3f & n2 = _refMesh->_normals[ _v2 ];
		return ( 1.0f - u - v ) * n0 + u * n1 + v * n2;
	}

	const Vec3f & TriangleMeshGeometry::getVecAt( uint i ) const { return _refMesh->_vertices[ _v[ i ] ]; }
	const Vec2f & TriangleMeshGeometry::getUVAt( uint i ) const { return _refMesh->_uvs[ _v[ i ] ]; }

	const float TriangleMeshGeometry::centroid( int axis )
	{
		return (1.0f / 3.0f)* ( _refMesh->_vertices[ _v0 ][ axis ] + _refMesh->_vertices[ _v1 ][ axis ]
				   + _refMesh->_vertices[ _v2 ][ axis ] );
	}

	bool TriangleMeshGeometry::operator==( const TriangleMeshGeometry & other )
	{
		return _v1 == other._v1 && _v2 == other._v2 && _v0 == other._v0;
	}

} // namespace RT_ISICG
