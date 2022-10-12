#ifndef __RT_ISICG_SCENE__
#define __RT_ISICG_SCENE__

#include "defines.hpp"
#include "lights/base_light.hpp"
#include "objects/base_object.hpp"
#include <exception>
#include <map>
#include <vector>

namespace RT_ISICG
{
	using ObjectMap		  = std::map<const std::string, BaseObject *>;
	using ObjectMapPair	  = ObjectMap::value_type;
	using MaterialMap	  = std::map<const std::string, BaseMaterial *>;
	using MaterialMapPair = MaterialMap::value_type;
	using LightList		  = std::vector<BaseLight *>;

	class Scene
	{
	  public:
		Scene();
		~Scene();

		// Hard coded initialization.
		void init();

		// Initialization from file.
		void init( const std::string & p_path );

		const LightList & getLights() const { return _lightList; }

		// animate for now just moving the circle backwards to see how the camera works
		void animate( const int frame );

		// Check for nearest intersection between p_tMin and p_tMax : if found fill p_hitRecord.
		bool intersect( const Ray & p_ray, const float p_tMin, const float p_tMax, HitRecord & p_hitRecord ) const;
		bool intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax ) const;

		void loadFileTriangleMesh( const std::string & p_name, const std::string & p_path );

		size_t getAnimationSize() { return _animations.size(); }

	  private:
		void _addObject( BaseObject * p_object );
		void _addMaterial( BaseMaterial * p_material );
		void _addLight( BaseLight * p_light );

		void _attachMaterialToObject( const std::string & p_materialName, const std::string & p_objectName );

	  private:
		ObjectMap	_objectMap;
		MaterialMap _materialMap;
		LightList	_lightList;

		std::vector<Vec3f>			_vertices;
		std::vector<unsigned short> _indices;
		std::vector<Vec3f>			_animations;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_SCENE__
