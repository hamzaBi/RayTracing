#ifndef __RT_ISICG_PATH_TRACING_INTEGRATOR__
#define __RT_ISICG_PATH_TRACING_INTEGRATOR__

#include "base_integrator.hpp"

namespace RT_ISICG
{
	class PathTracingIntegrator : public BaseIntegrator
	{
	  public:
		PathTracingIntegrator() : BaseIntegrator() {}
		virtual ~PathTracingIntegrator() = default;

		const IntegratorType getType() const override { return IntegratorType::PATH_TRACING; }

	  private:
		inline const Vec3f _getRandomRay( const Vec3f & dir ) const;

		// Return incoming luminance.
		Vec3f Li( const Scene & p_scene, const Ray & p_ray, const float p_tMin, const float p_tMax ) const override;

		Vec3f trace( const Scene & p_scene,
					 const Ray &   p_ray,
					 const float   p_tMin,
					 const float   p_tMax,
					 int		   p_bounces,
					 const bool	   inObject ) const;

		private:
			int _maxBounds = 2;
			int _nbSamples = 2;
			int _nbLightSamples = 4;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_PATH_TRACING_INTEGRATOR__
