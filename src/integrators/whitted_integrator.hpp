#ifndef __RT_ISICG_WHITTED_INTEGRATOR__
#define __RT_ISICG_WHITTED_INTEGRATOR__

#include "base_integrator.hpp"

namespace RT_ISICG
{
	class WhittedIntegrator : public BaseIntegrator
	{
	  public:
		WhittedIntegrator() : BaseIntegrator() {}
		virtual ~WhittedIntegrator() = default;

		const IntegratorType getType() const override { return IntegratorType::DIRECT_LIGHT; }
		inline void			 setNbLightSamples( const int p_nbLightSamples ) { _nbLightSamples = p_nbLightSamples; }

		// Return incoming luminance.
		Vec3f Li( const Scene & p_scene, const Ray & p_ray, const float p_tMin, const float p_tMax ) const override;

		Vec3f trace( const Scene & p_scene,
					 const Ray &   p_ray,
					 const float   p_tMin,
					 const float   p_tMax,
					 int		   p_bounces,
					 const bool	   inObject ) const;

	  private:
		int _nbLightSamples = 4;
		int _nbBounces		= 5;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_RAY_CAST_INTEGRATOR__
