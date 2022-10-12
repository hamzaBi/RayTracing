#ifndef __RT_ISICG_MAP_TEXTURE__
#define __RT_ISICG_MAP_TEXTURE__

#include "base_texture.hpp"
#include <vector>
#include "defines.hpp"
#include <iostream>

namespace RT_ISICG
{

	class MapTexture : public BaseTexture
	{

		public:
		  MapTexture()  = default;
		  MapTexture(const std::string & p_filename );
		  ~MapTexture() = default;

		  virtual Vec3f getPixel(const Vec2f& uv ) const override;

		private:
		  std::string				 _filename;
		  int						 _width;
		  int						 _height;
		  int						 _channels;
		  unsigned char *_pixels;

	};
}

#endif // !__RT_ISICG_CHECKER_TEXTURE__
