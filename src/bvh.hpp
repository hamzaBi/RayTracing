#ifndef __RT_ISICG_BVH__
#define __RT_ISICG_BVH__

#include "aabb.hpp"
#include "hit_record.hpp"
#include <tuple>
#include <vector>
namespace RT_ISICG
{
	class TriangleMeshGeometry;

	struct BVHNode
	{
		BVHNode() = default;
		~BVHNode()
		{
			delete _left;
			delete _right;
		}

		BVHNode( AABB aabb, uint p_firstTriangleId, uint p_lastTriangleId )
		{
			_aabb			 = aabb;
			_firstTriangleId = p_firstTriangleId;
			_lastTriangleId	 = p_lastTriangleId;
		}

		BVHNode( AABB aabb, std::vector<uint> indexes )
		{
			_aabb			 = aabb;
			_firstTriangleId = indexes[ 0 ];
			_lastTriangleId	 = indexes[ 1 ];
		}

		bool isLeaf() const { return ( _left == nullptr && _right == nullptr ); }

		AABB	  _aabb;
		BVHNode * _left			   = nullptr;
		BVHNode * _right		   = nullptr;
		uint	  _firstTriangleId = 0;
		uint	  _lastTriangleId  = 0;
	};

	class BVH
	{
	  public:
		BVH() = default;
		~BVH() { delete _root; }

		// Build the BVH from a list of triangles (call _buildRec).
		void build( std::vector<TriangleMeshGeometry> * p_triangles, AABB aabb );

		// Search for the nearest intersection with the ray (call _intersectRec).
		bool intersect( const Ray & p_ray, const float p_tMin, const float p_tMax, HitRecord & p_hitRecord ) const;
		// Search for the any intersection with the ray (call _intersectRec).
		bool intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax ) const;

	  private:
		void _buildRec( BVHNode * p_node,  uint p_firstTriangleId, uint p_lastTriangleId, int p_depth );

		bool _intersectRec( const BVHNode * p_node,
							const Ray &		p_ray,
							const float		p_tMin,
							const float		p_tMax,
							HitRecord &		p_hitRecord ) const;

		bool _intersectAnyRec( const BVHNode * p_node,
							   const Ray &	   p_ray,
							   const float	   p_tMin,
							   const float	   p_tMax ) const;

		void partition( BVHNode * p_node, uint fid, uint lid, float centre, uint largestAxis );
		void subdevision( BVHNode * p_node, std::vector<uint> world, float centre );

	  private:
		std::vector<TriangleMeshGeometry> * _triangles = nullptr;
		BVHNode *							_root	   = nullptr;

		const uint _maxTrianglesPerLeaf = 8;
		const uint _maxDepth			= 32;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_BVH__
