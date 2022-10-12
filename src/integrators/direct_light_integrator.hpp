#ifndef __RT_ISICG_DIRECT_LIGHT_INTEGRATOR__
#define __RT_ISICG_DIRECT_LIGHT_INTEGRATOR__

#include "base_integrator.hpp"

namespace RT_ISICG
{
	class DirectLightIntegrator : public BaseIntegrator
	{
	  public:
		DirectLightIntegrator() : BaseIntegrator() {}
		virtual ~DirectLightIntegrator() = default;

		const IntegratorType getType() const override { return IntegratorType::DIRECT_LIGHT; }
		inline void			 setNbLightSamples( const int p_nbLightSamples ) { _nbLightSamples = p_nbLightSamples; }

		// Return incoming luminance.
		Vec3f Li( const Scene & p_scene, const Ray & p_ray, const float p_tMin, const float p_tMax ) const override;

		private:
		int _nbLightSamples = 1;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_RAY_CAST_INTEGRATOR__
