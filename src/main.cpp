#include "cameras/perspective_camera.hpp"
#include "defines.hpp"
#include "renderer.hpp"

namespace RT_ISICG
{
	int main( int argc, char ** argv )
	{
		const int imgWidth	= 1920;
		const int imgHeight = 1080;

		// Create a texture to render the scene.
		Texture img = Texture( imgWidth, imgHeight );

		// Create and init scene.
		Scene scene;
		scene.init();
		// Create a perspective camera.
		// PerspectiveCamera camera( float( imgWidth ) / imgHeight );
		Vec3f			  position( 0.f, 3.f, -6.f ); //( 0.f, 2.0f, -6.0f );
		Vec3f			  lookAt( 0.f, 2.f, 1.0f );
		PerspectiveCamera camera( position, lookAt, Vec3f( .0f, 1.f, .0f ), 90.f, 1920.0f / 1080.0f );
		// Create and setup the renderer.
		Renderer renderer;
		renderer.setIntegrator( IntegratorType::PATH_TRACING );
		renderer.setBackgroundColor( GREY );

		// Launch rendering.
		std::cout << "Rendering..." << std::endl;
		std::cout << "- Image size: " << imgWidth << "x" << imgHeight << std::endl;

		float renderingTime = renderer.renderImage( scene, &camera, img );
		std::cout << "-> Done in " << renderingTime << "ms" << std::endl;
		// Save rendered image.
		const std::string imgName = "image.jpg";
		img.saveJPG( RESULTS_PATH + imgName );

		// camera.setFocalDistance( 1.0f );
		// camera.setApreture( 0.01f );
		// for (int i = 0; i < 25; i++) {
		//	float renderingTime = renderer.renderImage( scene, &camera, img );
		//	camera.setApreture( camera.getApreture() + 0.01 );
		//	std::cout << " Frame" << (i+1) <<"-> Done in " << renderingTime << "ms" << std::endl;
		//	// Save rendered image.
		//	const std::string imgName = "focalDistance_animation/image" + std::to_string( i+1 ) + ".jpg";
		//	img.saveJPG( RESULTS_PATH + imgName );
		//	//scene.animate(i);
		//}

		return EXIT_SUCCESS;
	}
} // namespace RT_ISICG

int main( int argc, char ** argv )
{
	try
	{
		return RT_ISICG::main( argc, argv );
	}
	catch ( const std::exception & e )
	{
		std::cerr << "Exception caught:" << std::endl << e.what() << std::endl;
	}
}
