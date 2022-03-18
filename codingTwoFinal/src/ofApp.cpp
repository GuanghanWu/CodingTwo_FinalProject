#include "ofApp.h"

//--------------------------------------------------------------
ofApp::~ofApp() {
	for (unsigned int i = 0; i < path.size(); ++i)
	{
		delete path[i];
	}
	for (unsigned int i = 0; i < particles.size(); ++i)
	{
		delete particles[i];
	}
}

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	ofSetFullscreen(1);
	center2D = ofVec3f(ofGetWidth() / 2, ofGetHeight() / 2);
	ofBackground(5, 5, 5);
	cam.setPosition(center2D.x, center2D.y, 1200);
	cam.setFarClip(10000);

	myMusic.load("AdventureTimeSection.mp3");
	myMusic.setVolume(0.7f);
	myMusic.play();

	ctSphere = new pathObj(center2D, ofVec3f(0));

	for (unsigned int i = 0; i < 48; ++i)
	{
		path.push_back(new pathObj());
	}
	for (unsigned int i = 0; i < 512; ++i)
	{
		particles.push_back(new randomObj());
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	//t += 0.6;// +0.02 * mouseWeight;
	t += 0.06;
	float* buf = ofSoundGetSpectrum(band);
	for (unsigned int i = 0; i < band; i++) {
		fft[i] *= 0.8f;//this right value higher, the display smoother.
		if (fft[i] < buf[i]) fft[i] = buf[i];
	}

	if (t < KeyFP[0])
	{
		//four corner circles
		float posWList[2] = { wUnit * 14 , ofGetWidth() - wUnit * 14 };
		float posHList[2] = { hUnit * 14 , ofGetHeight() - hUnit * 14 };

		// different circle style respectively
		for (unsigned int i = 0; i < path.size(); ++i)
		{
			if (i < path.size() / 4) path[i]->updateInCircle(t + i * 3.0, ofVec3f(posWList[0], posHList[0]), min(t*10, r));
			else if (i >= path.size() / 4 && i < path.size() / 2) path[i]->updateInCircle(-t + i * 2.0, ofVec3f(posWList[1], posHList[0]), min(t*10, r));
			else if (i >= path.size() / 2 && i < path.size() * 3 / 4) path[i]->updateInCircle(t + i * 1.0, ofVec3f(posWList[0], posHList[1]), min(t*10, r));
			else path[i]->updateInCircle(-t - i * 4.0, ofVec3f(posWList[1], posHList[1]), min(t*10, r));
			path[i]->setMainPointPos(path[0]->getPos());
		}
	}
	else if(t < KeyFP[2])
	{
		ofVec3f center2D = ofVec3f(ofGetWidth() / 2, ofGetHeight() / 2);
		// move to the center
		for (unsigned int i = 0; i < path.size(); ++i)
		{
			float rs[4] = {r,r,r,r};
			if(path[i]->centerPos != center2D) 
			{	
				path[i]->centerPos += (center2D - path[i]->centerPos) / 26;

				if (i < path.size() / 4 ) rs[0] = max(rs[0] - 0.2, rs[0] / 1.5);
				else if (i >= path.size() / 4 && i < path.size() / 2) rs[1] = max(rs[1] + 0.15f, rs[1] * 2.0f);
				else if (i >= path.size() / 2 && i < path.size() * 3 / 4)  rs[2] = max(rs[2] + 0.2f, rs[2] * 3);
				else rs[3] = max(rs[3] + 0.4f, rs[3] * 5);
			}
			if (i < path.size() / 4)
				path[i]->updateInCircle(t*4 + i * 3.0, path[i]->centerPos, rs[0]);
			else if (i >= path.size() / 4 && i < path.size() / 2) path[i]->updateInCircle(-t*4 + i * 2.0, path[i]->centerPos, rs[1]);
			else if (i >= path.size() / 2 && i < path.size() * 3 / 4) path[i]->updateInCircle(t + i * 1.0, path[i]->centerPos, rs[2]);
			else path[i]->updateInCircle(-t*0.4 - i * 4.0, path[i]->centerPos, rs[3]);
			path[i]->setMainPointPos(path[0]->getPos());
		}
	}
	else if (t < KeyFP[3])
	{// rise heights of some circles
		for (unsigned int i = 0; i < path.size(); ++i)
		{
			if (i < path.size() / 4)
			{
				path[i]->centerPos.z += 0.2;
				path[i]->update3DRot(t * 4 + i * 3.0, path[i]->centerPos, path[i]->rStore);
			}
			else if (i >= path.size() / 4 && i < path.size() / 2)
			{
				path[i]->centerPos.z += 0.6;
				path[i]->update3DRot(-t * 4 + i * 2.0, path[i]->centerPos, path[i]->rStore);
			}
			else if (i >= path.size() / 2 && i < path.size() * 3 / 4)
			{
				path[i]->centerPos.z += 1.2;
				path[i]->update3DRot(t + i * 1.0, path[i]->centerPos, path[i]->rStore);
			}
			else
			{
				path[i]->centerPos.z += 2;
				path[i]->update3DRot(-t * 0.4 - i * 4.0, path[i]->centerPos, path[i]->rStore);
			}
			path[i]->setMainPointPos(path[0]->getPos());
		}
	}
	
	if (t >= KeyFP[3] && initial == FALSE)// it's time to initial the mirror
	{
			for(unsigned int i = 0; i < path.size(); ++i)
			{
				pathMirror.push_back(new pathObj(*path[i]));
			}
			initial = TRUE;
	}

	if(t >= KeyFP[3] && t < KeyFP[4])// mirror's color change
	{
		for (unsigned int i = 0; i < path.size(); ++i)
		{
			ofVec3f centerPo = path[i]->centerPos;
			if (i < path.size() / 4)
			{
				path[i]->update3DRot(t * 4 + i * 3.0, centerPo, path[i]->rStore);
				pathMirror[i]->update3DRot(t * 4 + i * 3.0, ofVec3f(centerPo.x, centerPo.y,-centerPo.z), pathMirror[i]->rStore);
			}
			else if (i >= path.size() / 4 && i < path.size() / 2)
			{
				path[i]->update3DRot(-t * 4 + i * 2.0, centerPo, path[i]->rStore);
				pathMirror[i]->update3DRot(-t * 4 + i * 2.0, ofVec3f(centerPo.x, centerPo.y, -centerPo.z), pathMirror[i]->rStore);
			}
			else if (i >= path.size() / 2 && i < path.size() * 3 / 4)
			{
				path[i]->update3DRot(t + i * 1.0, centerPo, path[i]->rStore);
				pathMirror[i]->update3DRot(t + i * 1.0, ofVec3f(centerPo.x, centerPo.y, -centerPo.z), pathMirror[i]->rStore);
			}
			else
			{
				path[i]->update3DRot(-t * 0.4 - i * 4.0, centerPo, path[i]->rStore);
				pathMirror[i]->update3DRot(-t * 0.4 - i * 4.0, ofVec3f(centerPo.x, centerPo.y, -centerPo.z), pathMirror[i]->rStore);
			}
		}

	}
	if (t  >= KeyFP[4] && t  < KeyFP[5])// going on move the z
	{
		for (unsigned int i = 0; i < path.size(); ++i)
		{
			ofVec3f centerPo = path[i]->centerPos;
			if (i < path.size() / 4)
			{	
				
				path[i]->update3DRot(t * 4 + i * 3.0, centerPo, path[i]->rStore);
				pathMirror[i]->update3DRot(t * 4 + i * 3.0, ofVec3f(centerPo.x, centerPo.y, -centerPo.z), pathMirror[i]->rStore);
			}
			else if (i >= path.size() / 4 && i < path.size() / 2)
			{
				centerPo.z += 0.2;
				path[i]->update3DRot(-t * 4 + i * 2.0, centerPo, path[i]->rStore);
				pathMirror[i]->update3DRot(-t * 4 + i * 2.0, ofVec3f(centerPo.x, centerPo.y, -centerPo.z), pathMirror[i]->rStore);
			}
			else if (i >= path.size() / 2 && i < path.size() * 3 / 4)
			{
				centerPo.z -= 0.2;
				path[i]->update3DRot(t * 2 + i * 1.0, centerPo, path[i]->rStore);
				pathMirror[i]->update3DRot(t * 2 + i * 1.0, ofVec3f(centerPo.x, centerPo.y, -centerPo.z), pathMirror[i]->rStore);
			}
			else
			{
				centerPo.z -= 0.7;
				path[i]->update3DRot(-t * 2 - i * 4.0, centerPo, path[i]->rStore);
				pathMirror[i]->update3DRot(-t * 2 - i * 4.0, ofVec3f(centerPo.x, centerPo.y, -centerPo.z), pathMirror[i]->rStore);
			}
		}
	}
	else if (t >= KeyFP[5] && t < KeyFP[6])
	{//fade the shell
		for (unsigned int i = 0; i < path.size(); ++i)
		{
			ofVec3f centerPo = path[i]->centerPos;
			if (i < path.size() / 4)
			{
				path[i]->update3DRot(t * 4 + i * 3.0, centerPo, path[i]->rStore);
				pathMirror[i]->update3DRot(t * 4 + i * 3.0, ofVec3f(centerPo.x, centerPo.y, -centerPo.z), pathMirror[i]->rStore);
			}
			else if (i >= path.size() / 4 && i < path.size() / 2)
			{
				path[i]->update3DRot(-t * 4 + i * 2.0, centerPo, path[i]->rStore);
				pathMirror[i]->update3DRot(-t * 4 + i * 2.0, ofVec3f(centerPo.x, centerPo.y, -centerPo.z), pathMirror[i]->rStore);
			}
			else if (i >= path.size() / 2 && i < path.size() * 3 / 4)
			{
				path[i]->update3DRot(t + i * 1.0, centerPo, path[i]->rStore);
				pathMirror[i]->update3DRot(t + i * 1.0, ofVec3f(centerPo.x, centerPo.y, -centerPo.z), pathMirror[i]->rStore);
			}
			else
			{
				path[i]->update3DRot(-t * 0.4 - i * 4.0, centerPo, path[i]->rStore);
				pathMirror[i]->update3DRot(-t * 0.4 - i * 4.0, ofVec3f(centerPo.x, centerPo.y, -centerPo.z), pathMirror[i]->rStore);
			}
		}
	}
	else if (t >= KeyFP[6])// && t < KeyFP[7])
	{//move the z of left 1/4 ones
		for (unsigned int i = 0; i < path.size()/4; ++i)
		{
			ofVec3f centerPo = path[i]->centerPos;
			if(t< KeyFP[7]) centerPo.z += 0.05*i;
			path[i]->update3DRot(t * 4 + i * 3.0, centerPo, path[i]->rStore);
			pathMirror[i]->update3DRot(t * 4 + i * 3.0, ofVec3f(centerPo.x, centerPo.y, -centerPo.z), pathMirror[i]->rStore);
		}
	}
	for (unsigned int i = 0; i < particles.size(); ++i)
	{
		particles[i]->update(path[i%48],t);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	//the rectangles of music
	for (unsigned int i = 0; i < band; i++) {
		ofDrawRectangle(100 + i * 20, ofGetHeight() - 60, 20, -(fft[i] * 400));
	}

	//draw center sphere
	ofVec3f vc(0);
	for (unsigned int i = 0; i < 10; i++) {
		vc += ofVec3f(fft[i]*80.0f);
	}
	float radius=0;
	for (unsigned int i = 10; i < 30; i++) {
		radius += fft[i];
	}
	//cout << "vc.x,y,z" << vc.x << " " << vc.y << " " << vc.z << " " <<endl;
	ofSetColor(min(vc.x,140.0f), min(vc.y * 1.5f, 180.0f), min(vc.z * 1.8f, 220.0f),220);
	ofDrawSphere(ctSphere->getPos(), min(20.0f, radius * 30.0f + 2.0f));

	if (t < KeyFP[0])
	{
		//draw circles
		for (unsigned int i = 0; i < path.size(); ++i)
		{
			path[i]->draw(t);
		}
	}
	else if (t <= KeyFP[1])
	{
		//draw spheres
		for (unsigned int i = 0; i < path.size(); ++i)
		{
			path[i]->draw2(t);
		}
	}
	else
	{
		cam.begin();
		cam.disableMouseInput();
		//Attention! openGL use the left-hand-principle
		cam.lookAt(ofVec3f(ofGetWidth() / 2, ofGetHeight() / 2, 0), ofVec3f(0, 0, 1));
		if(cam.getPosition().z > 800) cam.move(5, 5, -2);

		if(t< KeyFP[5])
		{
			for (unsigned int i = 0; i < path.size(); ++i)
			{
				path[i]->draw2(t);

			}
		}
		if (t >= KeyFP[3] && t < KeyFP[5])// begin to draw the mirror
		{
			for (unsigned int i = 0; i < pathMirror.size(); ++i)
			{
				pathMirror[i]->mirrorDraw(t);

			}
		}
		else if (t >= KeyFP[5] && t < KeyFP[6])
		{
			for (unsigned int i = 0; i < path.size(); ++i)
			{
				if(i< path.size()/4)
				{
					path[i]->draw2(t);
					pathMirror[i]->mirrorDraw(t);
				}
				else
				{
					path[i]->drawFade(t,1);
					pathMirror[i]->drawFade(t,2);
				}
			}
		}
		else if(t >= KeyFP[6] && t < KeyFP[7])
		{
			for (unsigned int i = 0; i < path.size() / 4; ++i)
			{
				path[i]->drawEnd(t,i);
				pathMirror[i]->drawEnd(t,i);
			}
		}


		for (unsigned int i = 0; i < particles.size(); ++i)
		{
			particles[i]->draw(t);
		}
		cam.end();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

	//mouseWeight = 1.0*ofGetMouseX()/ofGetWidth()+1.0*ofGetMouseY()/ofGetHeight();
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
