#include "ofMain.h"
#include "ofApp.h"



//========================================================================
int main(int argc, char *argv[]) {
	if (argc != 3) {
		cout << "No arguments provided. Terminating" << endl;
		return 1;
	}
	cout << "Using \"" << argv[1] << "\" as texture file" << endl;
  cout << "Using " << argv[2] << " as time stamp" << endl;
	ofSetupOpenGL(600,600,OF_WINDOW);			// <-------- setup the GL context
	ofRunApp(new ofApp(argv[1], stoi(argv[2])));
	return 0;
}
