#include "renderer.hpp"
#include "integrators/direct_light_integrator.hpp"
#include "integrators/ray_cast_integrator.hpp"
#include "integrators/whitted_integrator.hpp"
#include "utils/console_progress_bar.hpp"
#include "utils/random.hpp"
#include <iostream>
#include "integrators/path_tracing_integrator.hpp"
#include <omp.h>

namespace RT_ISICG
{
	Renderer::Renderer() { _integrator = new RayCastIntegrator(); }

	void Renderer::setIntegrator( const IntegratorType p_integratorType )
	{
		if ( _integrator != nullptr ) { delete _integrator; }

		switch ( p_integratorType )
		{
		case IntegratorType::DIRECT_LIGHT:
		{
			_integrator = new DirectLightIntegrator();
			break;
		}
		case IntegratorType::WHITTED:
		{
			_integrator = new WhittedIntegrator();
			break;
		}
		case IntegratorType::PATH_TRACING:
		{
			_integrator = new PathTracingIntegrator();
			break;
		}
			
		case IntegratorType::RAY_CAST:
		default:
		{
			_integrator = new RayCastIntegrator();
			break;
		}
		}
	}

	void Renderer::setBackgroundColor( const Vec3f & p_color )
	{
		if ( _integrator == nullptr ) { std::cout << "[Renderer::setBackgroundColor] Integrator is null" << std::endl; }
		else
		{
			_integrator->setBackgroundColor( p_color );
		}
	}

	float Renderer::renderImage( const Scene & p_scene, const BaseCamera * p_camera, Texture & p_texture )
	{
		const int width	 = p_texture.getWidth();
		const int height = p_texture.getHeight();

		Chrono			   chrono;
		ConsoleProgressBar progressBar;

		progressBar.start( height, 50 );
		setNbPixelSamples( 128 );
		( (DirectLightIntegrator *)_integrator )->setNbLightSamples( 4 );
		chrono.start();
		#pragma omp parallel for schedule( dynamic )

		for ( int j = 0; j < height; j++ )
		{
			for ( int i = 0; i < width; i++ )
			{
				Vec3f finalColor( 0.0f );
				for ( int k = 0; k < _nbPixelSamples; k++ )
				{
					float randX = randomFloat();
					float randY = randomFloat();

					float x		  = (float)( i + randX ) / width;
					float y		  = (float)( j + randY ) / height;
					Vec3f tempCol = _integrator->Li( p_scene, p_camera->generateRay( x, y ), 1.0f, 150.0f );
					if ( glm::any( glm::isnan( tempCol ) ) ) tempCol = BLACK;
					finalColor	  = finalColor + tempCol;
				}
				

				finalColor = finalColor / (float)( _nbPixelSamples );
				p_texture.setPixel( i, j, glm::clamp( finalColor, Vec3f( .0f ), Vec3f( 1.f ) ) );
			}

			progressBar.next();
		}

		chrono.stop();
		progressBar.stop();

		return chrono.elapsedTime();
	}
} // namespace RT_ISICG
