#pragma once

#include "ofMain.h"
#include "ofxImGui.h"

#include "ofxXmlSettings.h"
#include "YAMPE/Particle.h"
#include "YAMPE/Particle/ForceGeneratorRegistry.h"
#include "YAMPE/Particle/ContactRegistry.h"
#include "YAMPE/Particle/ContactGenerators.h"
#include "PencilContactGenerator.h"
#include "PlaneContactGenerator.h"

class ofApp : public ofBaseApp {
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
		
    // simple 3D world with ground and axes
    const float RANGE = 16;
    ofEasyCam easyCam;
    float cameraHeightRatio = 0.02f;
    ofPoint easyCamTarget = ofPoint(0,5,0);
    void cameraHeightRatioChanged(float & cameraHeightRatio);

    ofPlanePrimitive ground;
    
    ofxImGui::Gui gui;                           // single entry to ImGUI subsystem
    ofRectangle mainWindowRectangle;        // used to ignore mouse drags for camera
    ofRectangle loggingWindowRectangle;     // used to ignore mouse drags for camera
    void drawAppMenuBar();
    void drawMainWindow();
    void drawLoggingWindow();
    
    // simimulation (generic)
    void reset();
    void quit();
    float t = 0.0f;
    bool isRunning = true;
	bool isStepping = false;

    ofParameter<bool> isAxisVisible = true;
    ofParameter<bool> isXGridVisible = false;
    ofParameter<bool> isYGridVisible = true;;
    ofParameter<bool> isZGridVisible = false;;
    ofParameter<bool> isGroundVisible = true;
    ofParameter<bool> isFullScreen;
    ofParameter<std::string> position;

    // TODO - simimulation (specific stuff)
	float elevation;
	int pencilSides;
	float pencilHeight;

	enum State {PLANE,SPHERE,PENCIL};
	int states [3] = { PLANE, SPHERE, PENCIL };
	int state;


	YAMPE::ParticleRegistry particles;
	YAMPE::P::ForceGeneratorRegistry forceGenerators;
	YAMPE::P::GravityForceGenerator::Ref gravity;

	YAMPE::P::ContactRegistry::Ref contacts;
	YAMPE::P::ParticleParticleContactGenerator ppContactGenerator;
	YAMPE::P::GroundContactGenerator groundContactGenerator;

	PencilContactGenerator pencilGenerator;
	PlaneContactGenerator planeGenerator;

	const int MAX_PENCIL_SIDES = 20;
	const int MIN_PENCIL_SIDES = 3;
	const float MAX_HEIGHT = 1.0f;
	const float MIN_HEIGHT = 0.0f;
	const float MAX_ELEVATION = 90.0f;
	const float MIN_ELEVATION = 0.0f;

	const float PENCIL_LENGTH = 10.0f;

private:

    // or here

};
