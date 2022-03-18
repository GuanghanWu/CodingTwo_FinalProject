#pragma once

#include "ofMain.h"
#include "elements.h"
#include <vector>

class ofApp : public ofBaseApp{

	public:
		~ofApp();
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
		float t = 0;
		float r = 80.0f;
		bool initial = FALSE;
		ofVec3f center2D;
		vector<pathObj*> path;
		vector<pathObj*> pathMirror;
		vector<randomObj*> particles;

		pathObj * ctSphere;// central element

		float mouseWeight;
		float hUnit = ofGetHeight() / 40;
		float wUnit = ofGetWidth() / 40;
		float KeyFP[8] = { r/5, 40, 52, 68, 100, 136, 164, 240};//key change frame point
		ofEasyCam cam;

		//following for music playing
		static constexpr size_t band = 128;
		std::array<float, band> fft{ {0} }; //fft stores sound buffer.
		ofSoundPlayer myMusic;

};
