#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "cinderSyphon.h"

using namespace ci;
using namespace ci::app;
using namespace std;

#define WIDTH 512
#define HEIGHT 512

class BasicSampleApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    
    gl::TextureRef	mLogo;
    
    syphonServer mTextureSyphon;
};

void BasicSampleApp::setup()
{
    mLogo = gl::Texture::create( loadImage( loadAsset("cinder_logo_alpha.png") ) );
    mTextureSyphon.setName("Cinder Texture Output");
}

void BasicSampleApp::mouseDown( MouseEvent event )
{
}

void BasicSampleApp::update()
{
}

void BasicSampleApp::draw()
{
    gl::enableAlphaBlending();
    
    gl::clear(Color::white());
    gl::color(ColorA(1.f, 1.f, 1.f, 1.f));

    gl::draw( mLogo, vec2(0,0) );
    

    // More or less works
    gl::pushMatrices();{
        mTextureSyphon.bind( mLogo->getSize() );
        gl::setMatricesWindow(WIDTH, HEIGHT, true);
        gl::ScopedViewport( 0,0,WIDTH, HEIGHT);
        
        gl::clear( Color(1,0,1) );
        gl::color( 1.0, 1.0, 1.0 );
        
        gl::draw( mLogo, vec2(cos(getElapsedSeconds() * 5), sin(getElapsedSeconds() * 5))*vec2(5.0) );
        mTextureSyphon.unbindAndPublish();
    }gl::popMatrices();
    
    // does not work
//    mTextureSyphon.publishTexture(mLogo);
}

CINDER_APP( BasicSampleApp, RendererGl, [&]( BasicSampleApp::Settings *settings){
    settings->setWindowSize(WIDTH, HEIGHT);
})
