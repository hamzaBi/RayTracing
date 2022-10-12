#ifndef __RT_ISICG_CHECKER_TEXTURE__
#define __RT_ISICG_CHECKER_TEXTURE__

#include "base_texture.hpp"

namespace RT_ISICG
{

	class CheckerTexture : public BaseTexture
	{

		public:
		  CheckerTexture()  = default;
		  ~CheckerTexture() = default;

		  virtual Vec3f getPixel(const Vec2f& uv ) const override;

	};
}

#endif // !__RT_ISICG_CHECKER_TEXTURE__
