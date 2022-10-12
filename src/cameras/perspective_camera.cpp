#include "perspective_camera.hpp"
#include <glm/gtx/string_cast.hpp>
#include "utils/random.hpp"

namespace RT_ISICG
{
	PerspectiveCamera::PerspectiveCamera( const float p_aspectRatio ) : _aspectRatio( p_aspectRatio )
	{
		_updateViewport();
	}

	PerspectiveCamera::PerspectiveCamera( const Vec3f & p_position,
										  const Vec3f & p_lookAt,
										  const Vec3f & p_up,
										  const float	p_fovy,
										  const float	p_aspectRatio )
		: BaseCamera( p_position ), _fovy( p_fovy ), _aspectRatio( p_aspectRatio )
	{
		/// TODO ! _u ? _v ? _w ?

		_w = glm::normalize(p_position - p_lookAt);
		_u = glm::normalize( cross( p_up, _w ) );
		_v = cross( _w, _u );

		_updateViewport();
	}

	inline Vec2f PerspectiveCamera::randomDisk() { 
		const float theta = randomFloat() * 2 * PIf;
		return Vec2f( glm::cos( theta ), glm::sin( theta ) ) * glm::sqrt( randomFloat() );
	}

	void PerspectiveCamera::_updateViewport()
	{
		/// TODO ! _viewportTopLeftCorner ?	_viewportU ? _viewportV ?
		
		
		float viewportHeight = 2.0f * tan( glm::radians( _fovy * 0.5f ) ) * _focalDistance;
		_viewportV			 = _v * viewportHeight;
		_viewportU			 = _u * viewportHeight * _aspectRatio;
		

		_viewportTopLeftCorner = _position + -_w * _focalDistance + _viewportV * 0.5f - _viewportU * 0.5f;
	}

} // namespace RT_ISICG
