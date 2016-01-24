#include "ofMain.h"
#include "ofApp.h"



//========================================================================
int main(int argc, char *argv[]) {
	if (argc != 2) {
		cout << "no arguments provided" << endl;
		return 1;
	}
	cout << "got " << argv[1] << endl;
	unsigned int fileid = 0;
	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context
	ofRunApp(new ofApp(&fileid, argv[1]));
	return fileid;
}
