#include "scene.hpp"
#include "lights/point_light.hpp"
#include "lights/quad_light.hpp"
#include "materials/color_material.hpp"
#include "materials/lambert_material.hpp"
#include "materials/matte_material.hpp"
#include "materials/microfacet_material.hpp"
#include "materials/mirror_material.hpp"
#include "materials/plastic_material.hpp"
#include "materials/transparent_material.hpp"
#include "objects/plane.hpp"
#include "objects/sphere.hpp"
#include "objects/triangle.hpp"
#include "objects/triangle_mesh.hpp"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include "materials/texture_material.hpp"

namespace RT_ISICG
{
	Scene::Scene() { _addMaterial( new ColorMaterial( "default", WHITE ) ); }

	Scene::~Scene()
	{
		for ( const ObjectMapPair & object : _objectMap )
		{
			delete object.second;
		}
		for ( const MaterialMapPair & material : _materialMap )
		{
			delete material.second;
		}
		for ( const BaseLight * light : _lightList )
		{
			delete light;
		}
	}

	void Scene::init()
	{
		// materials
		_addMaterial( new MatteMaterial( "CyanMatte", CYAN, 0.6f ) );
		_addMaterial( new MatteMaterial( "RedMatte", RED, 0.6f ) );
		_addMaterial( new MatteMaterial( "GreenMatte", GREEN, 0.6f ) );
		_addMaterial( new MatteMaterial( "BlueMatte", BLUE, 0.6f ) );
		_addMaterial( new MatteMaterial( "GreyMatte", GREY, 0.6f ) );
		_addMaterial( new MatteMaterial( "MagentaMatte", MAGENTA, 0.6f ) );
		_addMaterial( new MatteMaterial( "YellowMatte", YELLOW, 0.6f ) );
		

		_addObject( new Plane( "PlaneGround", Vec3f( 0.f, -3.f, 0.f ), Vec3f( 0.f, -1.f, 0.f ) ) );
		_attachMaterialToObject( "RedMatte", "PlaneGround" );
		_addObject( new Plane( "PlaneFront", Vec3f( 0.f, 0.f, 10.f ), Vec3f( 0.f, 0.f, 1.f ) ) );
		_attachMaterialToObject( "YellowMatte", "PlaneFront" );

		_addObject( new Plane( "PlaneLeft", Vec3f( 5.f, 0.f, 0.f ), Vec3f( 1.f, 0.f, 0.f ) ) );
		_attachMaterialToObject( "RedMatte", "PlaneLeft" );

		_addObject( new Plane( "PlaneCeiling", Vec3f( 0.f, 7.f, 0.f ), Vec3f( 0.f, 1.f, 0.f ) ) );
		_attachMaterialToObject( "GreenMatte", "PlaneCeiling" );

		_addObject( new Plane( "PlaneRight", Vec3f( -5.f, 0.f, 0.f ), Vec3f( -1.f, 0.f, 0.f ) ) );
		_attachMaterialToObject( "BlueMatte", "PlaneRight" );

		

#define SCENE_PROJET

#ifdef SCENE_TP5
		_addObject( new Sphere( "Sphere1", Vec3f( 0.f, 0.f, 3.f ), 2.5f ) );
		_attachMaterialToObject( "GreyMatte", "Sphere1" );

		/*_addObject( new Sphere( "Sphere2", Vec3f( 2.f, 0.f, 3.f ), 1.5f ) );
		_attachMaterialToObject( "TransparentMaterial", "Sphere2" );*/
		_addLight( new PointLight( WHITE, Vec3f( .0f, 5.0f, 0.f ), 100.f ) );
#endif
#ifdef SCENE_TP6
		//loadFileTriangleMesh( "bunny", DATA_PATH + "uvsphere.obj");
		//loadFileTriangleMesh( "cube", DATA_PATH + "Cube.obj" );
		_addObject( new Sphere( "Sphere1", Vec3f( 0.f, 0.f, 1.5f ), 1.5f ) );
		//_attachMaterialToObject( "TransparentMaterial", "bunny_defaultobject" );
		_attachMaterialToObject( "TransparentMaterial", "Sphere1" );
		 _addLight(new QuadLight(Vec3f(2.0f, 4.0f, 0.0f), Vec3f(-2.0f, 0.0f, 0.0f), Vec3f(0.0f, 0.0f, 2.0f),
		Vec3f(1.0f,1.0f,1.0f), 50.0f));
		//_addLight( new PointLight( WHITE, Vec3f( 0.0f, 5.0f, -4.f ), 170.f ) );
		//_addLight( new PointLight( WHITE, Vec3f( .0f, 5.0f, 0.f ), 150.f ) );
#endif
#ifdef SCENE_PROJET
		 //loadFileTriangleMesh( "refCube", DATA2_PATH + "refCube.obj" );
		 loadFileTriangleMesh( "frontWall", DATA2_PATH + "frontPlane.obj" );
		 loadFileTriangleMesh( "topWall", DATA2_PATH + "topPlane.obj" );
		 loadFileTriangleMesh( "bottomWall", DATA2_PATH + "floorPlane.obj" );
		 loadFileTriangleMesh( "leftWall", DATA2_PATH + "leftPlane.obj" );
		 loadFileTriangleMesh( "rightWall", DATA2_PATH + "rightPlane.obj" );
		 loadFileTriangleMesh( "windowFrame", DATA2_PATH + "windowFrame.obj" );
		 loadFileTriangleMesh( "windowGlass", DATA2_PATH + "windowGlass.obj" );
		 loadFileTriangleMesh( "tableTop", DATA2_PATH + "tableTop2.obj" );
		 loadFileTriangleMesh( "tableLegs", DATA2_PATH + "tableLegs.obj" );
		 loadFileTriangleMesh( "mirror", DATA2_PATH + "mirror.obj" );
		 loadFileTriangleMesh( "basket", DATA2_PATH + "basket.obj" );
		 loadFileTriangleMesh( "apples", DATA2_PATH + "apples.obj" );
		 loadFileTriangleMesh( "bunny1", DATA2_PATH + "bunny1.obj" );
		 loadFileTriangleMesh( "bunny2", DATA2_PATH + "bunny2.obj" );

	
		 _addObject( new Sphere( "lamp1", Vec3f(-4.f, 11.5f, 2.0f ), 0.5f) );
		 _addObject( new Sphere( "lamp2", Vec3f( 4.f, 11.5f, 2.0f ), 0.5 ) );

		 _attachMaterialToObject( "BlueMatte", "frontWall_front_Plane" );
		 _attachMaterialToObject( "YellowMatte", "topWall_top_Plane" );


		 
		 _addMaterial( new MirrorMaterial( "MirrorMaterial" ) );
		 _addMaterial( new TextureMaterial( "floorMaterial", TEXTURES_PATH + "floor1.jpg", WHITE, 32, 0.5f ) );
		 _addMaterial( new TextureMaterial( "bunnyTextureMaterial", TEXTURES_PATH + "bunny.png", WHITE, 32, 0.5f ) );
		 _addMaterial( new TextureMaterial( "apples", TEXTURES_PATH + "apples.jpg", GREEN, 32, 0.1 ) );

		 
		 _addMaterial( new TransparentMaterial( "tableTopMaterial", 2.0f ) );
		 _addMaterial( new TransparentMaterial( "TransparentMaterial", 2.418f) );
		 _addMaterial( new MicroFacetMaterial(
			 "basketMaterial", Vec3f( 0.69f, 0.39f, 0.09f ), Vec3f( 0.89f, 0.49f, 0.09f ), 0.3f, 0.6f ) );
		
		 _addMaterial( new PlasticMaterial(
			 "tableLegsMaterial", Vec3f( 0.6f, 0.5, 0.49 ), Vec3f( 0.8f, 0.74f, 0.69f ), 8, 0.7 ) );

		 _attachMaterialToObject( "floorMaterial", "bottomWall_bottom_Plane" );
		 _attachMaterialToObject( "RedMatte", "leftWall_left_Plane" );
		 _attachMaterialToObject( "GreyMatte", "rightWall_right_Plane" );
		 //_attachMaterialToObject( "GreyMatte", "refCube_refCube" );
		 _attachMaterialToObject( "BlueMatte", "windowFrame_windowFrame" );
		 _attachMaterialToObject( "tableTopMaterial", "tableTop_tableTop2" );
		 _attachMaterialToObject( "tableLegsMaterial", "tableLegs_tableLegs" );
		 _attachMaterialToObject( "YellowMatte", "lamp1" );
		 _attachMaterialToObject( "RedMatte", "lamp2" );
		 _attachMaterialToObject("basketMaterial", "basket_basket");
		 _attachMaterialToObject( "apples", "apples_apples");
		 _attachMaterialToObject( "bunnyTextureMaterial", "bunny1_Bunny" );
		 _attachMaterialToObject( "TransparentMaterial", "bunny2_Bunny" );



		 _addMaterial( new TransparentMaterial( "windowglassMaterial", 1.5f ) );
		 _attachMaterialToObject( "windowglassMaterial", "windowGlass_windowGlass" );
		 _attachMaterialToObject( "MirrorMaterial", "mirror_mirror" );



		 _addLight( new PointLight( WHITE, Vec3f( -4.f, 9.f, 2.0f ), 100.f ) );
		 _addLight( new PointLight( MAGENTA, Vec3f( 4.f, 9.f, 2.0f ), 80.f ) );
		 _addLight( new QuadLight(
			 Vec3f( -8.f, 3.55f, 0.f ), Vec3f( 0, 0, -3 ), Vec3f( 0, -3, 0 ), Vec3f( 1.f, 0.92f, 0.69f ), 35.f ) );

#endif
	}

	void Scene::loadFileTriangleMesh( const std::string & p_name, const std::string & p_path)
	{
		std::cout << "Loading: " << p_path << std::endl;
		Assimp::Importer importer;

		// Read scene and triangulate meshes
		const aiScene * const scene
			= importer.ReadFile( p_path, aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_GenUVCoords );

		if ( scene == nullptr ) { throw std::runtime_error( "Fail to load file: " + p_path ); }

		uint cptTriangles = 0;
		uint cptVertices  = 0;

		for ( uint m = 0; m < scene->mNumMeshes; ++m )
		{
			const aiMesh * const mesh = scene->mMeshes[ m ];
			if ( mesh == nullptr ) { throw std::runtime_error( "Fail to load file: " + p_path + ": mesh is null" ); }

			const std::string meshName = p_name + "_" + std::string( mesh->mName.C_Str() );
			std::cout << "-- Load mesh " << m + 1 << "/" << scene->mNumMeshes << ": " << meshName << std::endl;

			cptTriangles += mesh->mNumFaces;
			cptVertices += mesh->mNumVertices;

			const bool hasUV = mesh->HasTextureCoords( 0 );

			MeshTriangle * triMesh = new MeshTriangle( meshName );

			// Vertices before faces otherwise face normals cannot be computed.
			for ( uint v = 0; v < mesh->mNumVertices; ++v )
			{
				triMesh->addVertex( mesh->mVertices[ v ].x, mesh->mVertices[ v ].y, mesh->mVertices[ v ].z );
				triMesh->addNormal( mesh->mNormals[ v ].x, mesh->mNormals[ v ].y, mesh->mNormals[ v ].z );
				if ( hasUV ) triMesh->addUV( mesh->mTextureCoords[ 0 ][ v ].x, mesh->mTextureCoords[ 0 ][ v ].y );
			}
			for ( uint f = 0; f < mesh->mNumFaces; ++f )
			{
				const aiFace & face = mesh->mFaces[ f ];
				triMesh->addTriangle( face.mIndices[ 0 ], face.mIndices[ 1 ], face.mIndices[ 2 ] );
			}

			// if there are texture coordinates in the obj file we will load our texture
			

			_addObject( triMesh );
			triMesh->buildBVH();
			
			const aiMaterial * const mtl = scene->mMaterials[ mesh->mMaterialIndex ];
			if ( mtl == nullptr )
			{ std::cerr << "Material undefined," << meshName << " assigned to default material" << std::endl; }
			else
			{
				Vec3f kd = WHITE;
				Vec3f ks = BLACK;
				float s	 = 0.f;

				aiColor3D aiKd;
				if ( mtl->Get( AI_MATKEY_COLOR_DIFFUSE, aiKd ) == AI_SUCCESS ) kd = Vec3f( aiKd.r, aiKd.g, aiKd.b );
				aiColor3D aiKs;
				if ( mtl->Get( AI_MATKEY_COLOR_SPECULAR, aiKs ) == AI_SUCCESS ) ks = Vec3f( aiKs.r, aiKs.g, aiKs.b );
				float aiS = 0.f;
				if ( mtl->Get( AI_MATKEY_SHININESS, aiS ) == AI_SUCCESS ) s = aiS;
				aiString mtlName;
				mtl->Get( AI_MATKEY_NAME, mtlName );

				/*_addMaterial( new PlasticMaterial( std::string( mtlName.C_Str() ), kd, ks, s, 0.3f ) );
				_attachMaterialToObject( mtlName.C_Str(), meshName );*/
			}

			std::cout << "-- [DONE] " << triMesh->getNbTriangles() << " triangles, " << triMesh->getNbVertices()
					  << " vertices." << std::endl;
		}
		std::cout << "[DONE] " << scene->mNumMeshes << " meshes, " << cptTriangles << " triangles, " << cptVertices
				  << " vertices." << std::endl;
	}

	void Scene::init( const std::string & p_path ) {}

	bool Scene::intersect( const Ray & p_ray, const float p_tMin, const float p_tMax, HitRecord & p_hitRecord ) const
	{
		float tMax = p_tMax;
		bool  hit  = false;
		for ( const ObjectMapPair & object : _objectMap )
		{
			if ( object.second->intersect( p_ray, p_tMin, tMax, p_hitRecord ) )
			{
				tMax = p_hitRecord._distance; // update tMax to conserve the nearest hit
				hit	 = true;
			}
		}
		return hit;
	}

	bool Scene::intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax ) const
	{
		float tMax = p_tMax;
		bool  hit  = false;
		for ( const ObjectMapPair & object : _objectMap )
		{
			if ( object.second->intersectAny( p_ray, p_tMin, tMax ) )
			{
				hit = true;
				break;
			}
		}
		return hit;
	}

	void Scene::_addObject( BaseObject * p_object )
	{
		const std::string & name = p_object->getName();
		if ( _objectMap.find( name ) != _objectMap.end() )
		{
			std::cout << "[Scene::addObject] Object \'" << name << "\' already exists" << std::endl;
			delete p_object;
		}
		else
		{
			_objectMap[ name ] = p_object;
			_objectMap[ name ]->setMaterial( _materialMap[ "default" ] );
		}
	}

	void Scene::_addMaterial( BaseMaterial * p_material )
	{
		const std::string & name = p_material->getName();
		if ( _materialMap.find( name ) != _materialMap.end() )
		{
			std::cout << "[Scene::addMaterial] Material \'" << name << "\' already exists" << std::endl;
			delete p_material;
		}
		else
		{
			_materialMap[ name ] = p_material;
		}
	}

	void Scene::_addLight( BaseLight * p_light ) { _lightList.emplace_back( p_light ); }

	void Scene::_attachMaterialToObject( const std::string & p_materialName, const std::string & p_objectName )
	{
		if ( _objectMap.find( p_objectName ) == _objectMap.end() )
		{
			std::cout << "[Scene::attachMaterialToObject] Object \'" << p_objectName << "\' does not exist"
					  << std::endl;
		}
		else if ( _materialMap.find( p_materialName ) == _materialMap.end() )
		{
			std::cout << "[Scene::attachMaterialToObject] Material \'" << p_materialName << "\' does not exist, "
					  << "object \'" << p_objectName << "\' keeps its material \'"
					  << _objectMap[ p_objectName ]->getMaterial()->getName() << "\'" << std::endl;
		}
		else
		{
			_objectMap[ p_objectName ]->setMaterial( _materialMap[ p_materialName ] );
		}
	}

	void Scene::animate( const int frame )
	{
		/*_objectMap.erase( "Sphere1" );
		Vec3f pos = animations[ frame ];
		_addObject( new Sphere( "Sphere1", pos, 1.f ) );
		_attachMaterialToObject( "MatteGrey", "Sphere1" );*/
		_lightList.clear();
		Vec3f pos = _animations[ frame ];
		_addLight( new PointLight( WHITE, pos, 60.f ) );
	}

} // namespace RT_ISICG
