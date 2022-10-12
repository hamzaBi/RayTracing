#include "bvh.hpp"
#include "geometry/triangle_mesh_geometry.hpp"
#include "utils/chrono.hpp"
#include <algorithm>

namespace RT_ISICG
{
	void BVH::build( std::vector<TriangleMeshGeometry> * p_triangles, AABB aabb )
	{
		std::cout << "Building BVH..." << std::endl;
		if ( p_triangles == nullptr || p_triangles->empty() )
		{
			throw std::exception( "BVH::build() error: no triangle provided" );
		}
		_triangles = p_triangles;

		Chrono chr;
		chr.start();
		

		_root = new BVHNode( aabb, 0, (*_triangles).size() );
		_buildRec( _root, 0, ( *_triangles ).size(), 0 );

		chr.stop();

		std::cout << "[DONE]: " << chr.elapsedTime() << "s" << std::endl;
	}

	bool BVH::intersect( const Ray & p_ray, const float p_tMin, const float p_tMax, HitRecord & p_hitRecord ) const
	{
		return _intersectRec( _root, p_ray, p_tMin, p_tMax, p_hitRecord );
	}

	bool BVH::intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax ) const
	{
		return _intersectAnyRec( _root, p_ray, p_tMin, p_tMax );
		/// TODO
	}

	

	void BVH::partition( BVHNode * p_node, uint fid, uint lid, float centre, uint largestAxis ) {
		AABB Left, Right;
		uint i = fid;
		uint j = lid - 1;
		while ( i <= j )
		{
			float			   barycenter = ( *_triangles )[ i ].centroid( largestAxis );
			std::vector<Vec3f> vertices	  = { ( *_triangles )[ i ].getVecAt( 0 ),
											  ( *_triangles )[ i ].getVecAt( 1 ),
											  ( *_triangles )[ i ].getVecAt( 2 ) };
			if (barycenter > centre) {
				for ( int k = 0; k < 3; k++ )
					Right.extend( vertices[ k ] );
				std::swap( *( ( *_triangles ).begin() + i ), *( ( *_triangles ).begin() + j ) );
				j--;
				continue;
			}
			for ( int k = 0; k < 3; k++ )
				Left.extend( vertices[ k ] );

			i++;
		}

		
		p_node->_left					= new BVHNode( Left, fid, i );
		p_node->_right					= new BVHNode( Right, i, lid );
	}

	void BVH::_buildRec( BVHNode * p_node,  uint p_firstTriangleId, uint p_lastTriangleId, int p_depth )
	{
		if ( p_depth == _maxDepth || p_lastTriangleId - p_firstTriangleId < _maxTrianglesPerLeaf ) return;
		uint  largestAxis = p_node->_aabb.largestAxis();
		float			  center	  = p_node->_aabb.centroid()[ largestAxis ];
		

		partition( p_node, p_firstTriangleId, p_lastTriangleId, center, largestAxis );
		_buildRec( p_node->_left, p_firstTriangleId, p_node->_left->_lastTriangleId, p_depth + 1 );
		_buildRec( p_node->_right, p_node->_left->_lastTriangleId, p_lastTriangleId, p_depth + 1 );
		/// TODO
	}

	bool BVH::_intersectRec( const BVHNode * p_node,
							 const Ray &	 p_ray,
							 const float	 p_tMin,
							 const float	 p_tMax,
							 HitRecord &	 p_hitRecord ) const
	{
		bool intersection_b = p_node->_aabb.intersect( p_ray, p_tMin, p_tMax );
		if ( !intersection_b ) return false;

		if ( !p_node->isLeaf() )
		{
			HitRecord		  leftHit;
			HitRecord		  rightHit;
			bool			  leftIntersection = _intersectRec( p_node->_left, p_ray, p_tMin, p_tMax, leftHit );
			bool			  rightIntersection = _intersectRec( p_node->_right, p_ray, p_tMin, p_tMax, rightHit );


			if (leftIntersection && rightIntersection) {
				if ( rightHit._distance < leftHit._distance )
					p_hitRecord = rightHit;
				else
					p_hitRecord = leftHit;
				return true;
			}
			else if ( rightIntersection )
			{
				p_hitRecord = rightHit;
				return true;
			}
			else if ( leftIntersection )
			{
				p_hitRecord = leftHit;
				return true;
			}

			
		}
		else
		{
			float  tClosest = p_tMax;				   // Hit distance.
			size_t hitTri	= p_node->_lastTriangleId; // Hit triangle id.
			if ( !p_node->_aabb.intersect( p_ray, p_tMin, p_tMax ) ) return false;
			Vec2f uv( 0.f, 0.f );
			for ( size_t i = p_node->_firstTriangleId; i < p_node->_lastTriangleId; i++ )
			{
				float t;

				if ( ( *_triangles )[ i ].intersect( p_ray, t, uv ) )
				{
					if ( t >= p_tMin && t <= tClosest )
					{
						tClosest			= t;
						hitTri				= i;
						p_hitRecord._normal = ( *_triangles )[ hitTri ].computeNormal( uv );
					}
				}
			}
			if ( hitTri != p_node->_lastTriangleId ) // Intersection found.
			{
				p_hitRecord._point = p_ray.pointAtT( tClosest );
				p_hitRecord.faceNormal( p_ray.getDirection() );
				p_hitRecord._distance = tClosest;
				p_hitRecord._uvs[ 0 ] = ( *_triangles )[ hitTri ].getUVAt( 0 );
				p_hitRecord._uvs[ 1 ] = ( *_triangles )[ hitTri ].getUVAt( 1 );
				p_hitRecord._uvs[ 2 ] = ( *_triangles )[ hitTri ].getUVAt( 2 );
				p_hitRecord._uvs[ 3 ] = Vec2f( uv.x, uv.y );
				return true;
			}
		}

		return false;

		/// TODO
	}
	bool BVH::_intersectAnyRec( const BVHNode * p_node,
								const Ray &		p_ray,
								const float		p_tMin,
								const float		p_tMax ) const
	{
		if ( p_node->_aabb.intersect( p_ray, p_tMin, p_tMax ) )
		{
			if ( p_node->isLeaf() )
			{
				glm::vec2 normal;
				int		  i = p_node->_firstTriangleId;
				while ( i < p_node->_lastTriangleId )
				{
					float intersect_;
					bool  intersection_ray_object = ( *_triangles )[ i ].intersect( p_ray, intersect_, normal );

					if ( intersection_ray_object && intersect_ >= p_tMin && intersect_ <= p_tMax ) return true;
					i++;
				}
				return false;
			}
			else
			{
				return _intersectAnyRec( p_node->_left, p_ray, p_tMin, p_tMax )
					   || _intersectAnyRec( p_node->_right, p_ray, p_tMin, p_tMax );
			}
		}
		/// TODO
		return false;
	}
} // namespace RT_ISICG
