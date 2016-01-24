#include "ofApp.h"

Star::Star(float p, float t, float r, ofColor c)
{
	color = c;
	phi = p;
	theta = t;
	radius = r;
}


void Star::draw() {
	ofSetColor(color);
	ofDrawSphere(radius*cos(theta), radius*tan(phi), radius*sin(theta), 1);
}

//--------------------------------------------------------------

ofApp::ofApp(unsigned int *f, char *fnamein) {
	fileid = f;
	fname = fnamein;
}

void ofApp::setup() {
	snapCounter = 0;
	bSnapshot = true;
	phase = 0;
	radius = 30;
	rotationRadius = 500;

	lightSource = ofLight();
	lightSource.setPointLight();
	lightSource.setAttenuation(0.15f, 0.0013f, 0.f);

	// setup colors
	ofColor colors[4] = { ofColor(255, 100, 100), ofColor(255, 255, 100), ofColor(255, 255, 255), ofColor(100, 100, 255) };
	// randomly select a color from 0.0-1.0
	float colorRatio = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	if (colorRatio > 0.666f) {
		lightColor = colors[2].getLerped(colors[3], (colorRatio-0.666f)/(1-0.666f));
	}
	else if (colorRatio > 0.333f) {
		lightColor = colors[1].getLerped(colors[2], (colorRatio - 0.333f) / (0.666f - 0.333f));
	}
	else{
		lightColor = colors[0].getLerped(colors[1], colorRatio / (0.333f));
	}
	cout << lightColor << endl;
	lightSource.setDiffuseColor(ofColor(255,255,255));
	lightSource.setSpecularColor(lightColor);
	lightSource.setPosition((cos(phase) * rotationRadius), 0, sin(phase) * rotationRadius);

	//material.setShininess(40);
	//material.setSpecularColor(lightColor);

	// setup stars
	int numStars = 200 + rand() % 200;
	for (int i = 0; i < numStars; i++) {
		float theta = (float)rand();
		float phi = (float)rand();
		stars.push_back(Star(theta, phi, 2 * rotationRadius, ofColor(255, 255, 255)));
	}

	// setup camera
	camera.setPosition(150*sin((float)rand()), 150*sin((float)rand()), 150*sin((float)rand()));
	camera.lookAt(ofVec3f(0.f,0.f,0.f));

	// GL configs
	ofSetVerticalSync(true);
	ofEnableDepthTest();
	ofSetSmoothLighting(true);
	ofSetSphereResolution(64);
	ofDisableArbTex();
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glLightModelf(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
	
	// load texture
	imgIn.loadImage(fname);
	texture = imgIn.getTexture();
	glEnable(GL_DEPTH_TEST);

	quadric = gluNewQuadric();         // Create A Pointer To The Quadric Object  
	gluQuadricTexture(quadric, GL_TRUE);      // Create Texture Coords  
	gluQuadricNormals(quadric, GLU_SMOOTH);   // Create Smooth Normals

}


//--------------------------------------------------------------
void ofApp::update() {	
}


//--------------------------------------------------------------
void ofApp::draw() {
	// draw background
	ofBackground(0, 0, 0);

	camera.begin();

	for_each(stars.begin(), stars.end(), [](Star star) {
		star.draw();
	});

	// draw lightSource();
	ofSetColor(lightColor);
	ofDrawSphere(lightSource.getPosition(), 2);
	lightSource.enable();

	// draw image
	ofEnableLighting();
	ofEnableAlphaBlending();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// draw planet
	material.begin();
	texture.bind();
	gluSphere(quadric, radius, 100, 100); 
	texture.unbind();
	material.end();

	glDisable(GL_BLEND);
	ofDisableAlphaBlending();
	ofDisableLighting();
	camera.end();

	// take snapshot
	img.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
	int id = ofGetUnixTime();
	string fileName = "planet_" + ofToString(id) + ".png";
	img.save(fileName);
	*fileid = id;
	cout << "saved " << fileName << endl;
	std::exit(0); // we did it!

}


//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'a' || key == 's' || key == 'd' || key == 'q' || key == 'w' || key == 'e') {
		float con = lightSource.getAttenuationConstant();
		float lin = lightSource.getAttenuationLinear();
		float quad = lightSource.getAttenuationQuadratic();
		if (key == 'a') {
			lightSource.setAttenuation(con-0.01, lin, quad);
		}
		if (key == 's') {
			lightSource.setAttenuation(con, lin-0.0001, quad);
		}
		if (key == 'd') {
			lightSource.setAttenuation(con, lin, quad- 0.000001);
		}
		if (key == 'q') {
			lightSource.setAttenuation(con+0.01, lin, quad);
		}
		if (key == 'w') {
			lightSource.setAttenuation(con, lin+0.0001, quad);
		}
		if (key == 'e') {
			lightSource.setAttenuation(con, lin, quad+0.000001);
		}
		cout << lightSource.getAttenuationConstant() << " "
			<< lightSource.getAttenuationLinear() << " "
			<< lightSource.getAttenuationQuadratic() << endl;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}


//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
