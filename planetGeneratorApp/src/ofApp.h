#pragma once

#include "ofMain.h"
#include "of3dGraphics.h"

class Star
{
public:
	Star(float, float, float, ofColor);
	void draw();

	ofColor color;
	float phi;
	float theta;
	float radius;

};

class ofApp : public ofBaseApp {

public:

	int border = 100;

	int imageWidth = 300;
	int imageHeight = 300;


	ofApp(char * fnamein, unsigned int i);
	unsigned int id;
	char *fname;

	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	int 				  snapCounter;
	string 				  snapString;
	ofImage 			  img;
	bool 				  bSnapshot;
	float 				  phase;
	float         cameraTheta;
	float         cameraPhi;
	float				  radius;
	float				  rotationRadius;
	
	int numStars;
	std::vector<Star> stars;
	

	ofImage imgIn;
	ofTexture texture;
	GLUquadricObj *quadric;
	ofMaterial material;
	
	ofColor				  lightColor;
	ofLight				  lightSource;

	ofCamera              camera;


};

