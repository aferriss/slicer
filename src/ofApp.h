#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

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
        void genXYPositions();
    
    ofImage img, img2, carl, fang, jenn, emma, kathy;
    vector<ofImage> scientists;
    ofFbo fbo, post;
    int w, h;
    
    vector<int> yPositions;
    vector<int> xPositions;
    
    bool save;
    bool doWidth, copyToImg, justRendered;
    string file;
    ofEasyCam cam;
    ofShader shader;
};
