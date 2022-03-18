#pragma once
#include "ofMain.h"

class object
{
	//this is a virtual base class, so will have no realization
private:
	ofVec3f pos;// position;
	ofVec3f vel;// velocity;

	float appealWeight;//the weight of appealing compared to repeling
	float repelWeight;

	float appealHood;// the size of appealing
	float repelHood;// the size of appealing

public:
	//change the pos or vel or Hood
	virtual void setPos(ofVec3f);
	virtual void setVel(ofVec3f);
	virtual void setAppealHood(float);
	virtual void setRepelHood(float);

	//get the private values
	virtual ofVec3f getPos();
	virtual ofVec3f getVel();
	virtual float getAppealHood();
	virtual float getRepelHood();

	//do the actions!
	virtual ofVec3f appeal();//let the object chasing other objects
	virtual ofVec3f repel();//to repel other obects
	virtual void update();// the danamics need the update per frametime;
	virtual void draw();//virtual draw, would be rewriten by sons
};

class pathObj : public object
{
private:
	ofVec3f pos;
	ofVec3f vel;
	ofVec3f mainPointPos;
	float appealWeight;
	float repelWeight;
	float appealHood;
	float repelHood;
public:
	pathObj();
	pathObj(ofVec3f, ofVec3f);
	pathObj(const pathObj &pa);//This copy constructor is mainly used to create the mirror elements
	ofVec3f centerPos;
	float rStore;

	//~pathObj();

	virtual void setPos(ofVec3f);
	virtual void setMainPointPos(ofVec3f);
	virtual void setVel(ofVec3f);
	virtual void setAppealHood(float);
	virtual void setRepelHood(float);

	virtual ofVec3f getPos();
	virtual ofVec3f getMainPointPos();
	virtual ofVec3f getVel();
	virtual float getAppealHood();
	virtual float getRepelHood();

	void updateInCircle(float t, ofVec3f centerPos, float r);//let corners' elements shape a circle
	void update3DRot(float t, ofVec3f centerPos, float r);//to meet the need when transform to 3D
	void draw(float t);
	void draw2(float t);
	void mirrorDraw(float t);
	
	void drawFade(float t, int);
	
	void drawEnd(float t,int count);
};


class randomObj : public object
{
private:
	ofVec3f pos;
	ofVec3f vel;
	float appealWeight;
	float repelWeight;
	float appealHood;
	float repelHood;

public:
	randomObj();//initializing the private values(randomly);
	randomObj(ofVec3f, ofVec3f, float aW = 1.0, float rW = 0.4, float aH = 300.0, float rH = 20.0);

	//~randomObj();
	float distance;
	virtual void setPos(ofVec3f);
	virtual void setVel(ofVec3f);
	virtual void setAppealHood(float);
	virtual void setRepelHood(float);

	virtual ofVec3f getPos();
	virtual ofVec3f getVel();
	virtual float getAppealHood();
	virtual float getRepelHood();

	//this functions are inspired by the boids taught by Mick!
	ofVec3f appeal(pathObj* otherObj);
	ofVec3f appeal(vector < pathObj*> & otherObj);
	ofVec3f repel(pathObj* otherObj);
	ofVec3f repel(vector < pathObj*> & otherObj);
	void update(pathObj* otherObj, float t);
	void update(vector<pathObj*>& otherObj,float t);
	void draw(float t);

};