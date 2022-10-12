#ifndef  __RT_ISICG_BASE_TEXTURE__
#define __RT_ISICG_BASE_TEXTURE__

#include <string>
#include "defines.hpp"
namespace RT_ISICG{
	class BaseTexture
	{
	  public:
		BaseTexture() = default;
		virtual ~BaseTexture() = default;

		virtual Vec3f getPixel(const Vec2f & uv) const = 0;

		
	};
}

#endif // ! __RT_ISICG_BASE_TEXTURE__
