#ifndef __RT_ISICG_PERSPECTIVE_CAMERA__
#define __RT_ISICG_PERSPECTIVE_CAMERA__

#include "base_camera.hpp"

namespace RT_ISICG
{
	class PerspectiveCamera : public BaseCamera
	{
	  public:
		PerspectiveCamera( const float p_aspectRatio );

		PerspectiveCamera( const Vec3f & p_position,
						   const Vec3f & p_lookAt,
						   const Vec3f & p_up,
						   const float	 p_fovy,
						   const float	 p_aspectRatio );

		~PerspectiveCamera() = default;

		inline Ray generateRay( const float p_sx, const float p_sy ) const override
		{
			Vec3f pixel = _viewportTopLeftCorner + p_sx * _viewportU - p_sy * _viewportV;

			Vec3f dir = pixel - _position;

			return Ray( _position, glm::normalize( dir ) );
			
		}

		/*inline Ray generateRay(const float p_sx, const float p_sy) const override { 
			Vec3f focalPoint	  = _position + _viewportTopLeftCorner + _viewportU * p_sx - _viewportV * p_sy;
			Vec2f disk = randomDisk() * _apreture;
			Vec3f aperatureOrigin = _position + disk.x * _u + disk.y * _v;
			return Ray( aperatureOrigin, glm::normalize( focalPoint - aperatureOrigin ) );
		}*/

		static inline Vec2f randomDisk();
		float				getFocalDistance() const { return _focalDistance; }
		void setFocalDistance( const float & p_focalDistance ) { _focalDistance = p_focalDistance; }
		float				getApreture() const { return _apreture; }
		void				setApreture( float p_apreture ) { _apreture = p_apreture; }
	  private:
		void _updateViewport();
		

	  private:
		float _fovy			 = 60.f;
		float _focalDistance = 10.f;
		float _aspectRatio	 = 1.f;

		// Local coordinates system
		Vec3f _u = Vec3f( 1.f, 0.f, 0.f );
		Vec3f _v = Vec3f( 0.f, 1.f, 0.f );
		Vec3f _w = Vec3f( 0.f, 0.f, -1.f );

		// Viewport data
		Vec3f _viewportTopLeftCorner = VEC3F_ZERO; // Top left corner position
		Vec3f _viewportU			 = VEC3F_ZERO; // Horizontal vector
		Vec3f _viewportV			 = VEC3F_ZERO; // Vertical vector
		float _apreture				 = 0.1f;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_PERSPECTIVE_CAMERA__
