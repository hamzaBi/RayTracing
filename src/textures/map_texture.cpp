#include "map_texture.hpp"
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#endif
namespace RT_ISICG
{


	MapTexture::MapTexture(const std::string & p_filename) :
		_filename(p_filename) {
		_pixels = stbi_load( _filename.c_str(), &_width, &_height, &_channels, 0 );
		std::cout << "loading texture constructor" << std::endl;
		if ( _pixels == NULL )
		{
			std::cout << "unable to load texture : " << _filename << std::endl;
			exit( -1 );
		}
	}

	Vec3f MapTexture::getPixel(const Vec2f& uv) const { 
		
		const int		x			= abs(uv.x) * _width;
		const int		y			= abs(uv.y) * _height;
		const stbi_uc * pixelOffset = _pixels + ( _channels * ( y * _width + x ) );
		unsigned char	red			= pixelOffset[ 0 ];
		unsigned char	green		= pixelOffset[ 1 ];
		unsigned char	blue		= pixelOffset[ 2 ];
		//unsigned char	alpha		= _channels >= 4 ? pixelOffset[ 3 ] : 0xff;
		float fred	 = red / 255.0f;
		float fgreen = green / 255.0f;
		float fblue	 = blue / 255.0f;
		return Vec3f( fred, fgreen, fblue );
			

		
		
		
	}



}