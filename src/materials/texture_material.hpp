#ifndef __RT_ISICG_TEXTURE_MATERIAL__
#define __RT_ISICG_TEXTURE_MATERIAL__

#include "base_material.hpp"
#include "defines.hpp"
#include "brdfs/lambert_brdf.hpp"
#include "brdfs/phong_brdf.hpp"
#include "textures/map_texture.hpp"

namespace RT_ISICG
{
	class TextureMaterial : public BaseMaterial
	{
	  public:
		TextureMaterial( const std::string & p_name, const std::string & p_filename, const Vec3f & p_ks, const float & p_s, const float & p_spec )
			: BaseMaterial( p_name ), _filename( p_filename ), _lambert( WHITE ), _phong( BLACK, p_ks, p_s ), _spec(p_spec)
		{
			_texture = new MapTexture( _filename );
		}

		virtual ~TextureMaterial() = default;

		Vec3f shade( const Ray & p_ray, const HitRecord & p_hit, const LightSample & p_lightSample ) const override
		{

			Vec3f v1Color = _texture->getPixel( p_hit._uvs[ 0 ] );
			Vec3f v2Color = _texture->getPixel( p_hit._uvs[ 1 ] );
			Vec3f v3Color = _texture->getPixel( p_hit._uvs[ 2 ] );
			Vec2f uv		= p_hit._uvs[ 3 ];
			Vec3f col	  = ( 1.0f - uv.x - uv.y ) * v1Color + uv.x * v2Color + uv.y * v3Color;
			Vec3f phong	  = _phong.evaluate( -p_ray.getDirection(), p_lightSample._direction, p_hit._normal );
			Vec3f lambert = _lambert.evaluate();
			return ( _spec * phong + ( 1.0f - _spec ) * lambert ) * col; 
			
		}

		inline const Vec3f & getFlatColor() const override { return BLACK; }

	  protected:
		LambertBRDF _lambert;
		PhongBRDF	_phong;
		MapTexture * _texture;
		std::string _filename;
		float		 _spec;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_COLOR_MATERIAL__
