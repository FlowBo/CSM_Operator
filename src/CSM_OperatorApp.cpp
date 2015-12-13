#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class CSM_OperatorApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void CSM_OperatorApp::setup()
{
}

void CSM_OperatorApp::mouseDown( MouseEvent event )
{
}

void CSM_OperatorApp::update()
{
}

void CSM_OperatorApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP( CSM_OperatorApp, RendererGl )
