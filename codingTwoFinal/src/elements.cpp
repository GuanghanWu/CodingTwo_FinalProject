#include "elements.h"



void object::setPos(ofVec3f p)
{
	this->pos = p;
}

void object::setVel(ofVec3f v)
{
	this->vel = v;
}

void object::setAppealHood(float aH)
{
	this->appealHood = aH;
}

void object::setRepelHood(float rH)
{
	this->appealHood = rH;
}

ofVec3f object::getPos()
{
	return this->pos;
}

ofVec3f object::getVel()
{
	return this->vel;
}

float object::getAppealHood()
{
	return this->appealHood;
}

float object::getRepelHood()
{
	return this->repelHood;
}

ofVec3f object::appeal()
{
	return ofVec3f();
}

ofVec3f object::repel()
{
	return ofVec3f();
}

void object::update()
{
}

void object::draw()
{
}



/* pathObj's definitions : */

pathObj::pathObj()
{
	/*this->pos = ofVec3f(ofRandom(100), ofRandom(100));
	this->vel = ofVec3f(ofRandom(5), ofRandom(5));*/
	setPos(ofVec3f(ofRandom(100), ofRandom(100)));
	setVel(ofVec3f(ofRandom(5), ofRandom(5)));
}

pathObj::pathObj(ofVec3f posIn, ofVec3f velIn)
{
	this->pos = posIn;
	this->vel = velIn;
}

pathObj::pathObj(const pathObj& pa)
{
	this->mainPointPos = pa.mainPointPos;
	this->appealWeight = pa.appealWeight;
	this->repelWeight = pa.repelWeight;
	this->appealHood = pa.appealHood;
	this->repelHood = pa.repelHood;
	this->rStore = pa.rStore;

	pos = ofVec3f();
	vel = ofVec3f();
	centerPos = ofVec3f();
	pos = pa.pos;
	vel = pa.vel;
	centerPos = ofVec3f(pa.centerPos.x, pa.centerPos.y, -pa.centerPos.z);
	
}

//pathObj::~pathObj()
//{
//}
void pathObj::setPos(ofVec3f p)
{
	this->pos = p;
}

void pathObj::setMainPointPos(ofVec3f p)
{
	mainPointPos = p;
}

void pathObj::setVel(ofVec3f v)
{
	this->vel = v;
}

void pathObj::setAppealHood(float aH)
{
	this->appealHood = aH;
}

void pathObj::setRepelHood(float rH)
{
	this->appealHood = rH;
}

ofVec3f pathObj::getPos()
{
	return this->pos;
}

ofVec3f pathObj::getMainPointPos()
{
	return mainPointPos;
}

ofVec3f pathObj::getVel()
{
	return this->vel;
}

float pathObj::getAppealHood()
{
	return this->appealHood;
}

float pathObj::getRepelHood()
{
	return this->repelHood;
}



void pathObj::updateInCircle(float t, ofVec3f centerPos, float r)
{
	this->rStore = r;
	this->centerPos = centerPos;
	ofVec2f pos2D = ofVec2f(cos(t) * r + centerPos.x, sin(t) * r + centerPos.y);
	this->setPos(ofVec3f(pos2D));
}
void pathObj::update3DRot(float t, ofVec3f centerPos, float r)
{
	this->rStore = r;
	this->centerPos = centerPos;
	ofVec3f pos3D = ofVec3f(cos(t) * r + centerPos.x, sin(t) * r + centerPos.y, centerPos.z);
	this->setPos(pos3D);
}

void pathObj::draw(float t)
{	
	ofSetColor(200- t/2, 80- t/6, int(t*10)%255);
	ofDrawCircle(pos, 4);
}

void pathObj::draw2(float t)
{
	ofSetColor(200 - t / 2, 80 - t / 6, int(t * 10) % 255);
	float dis = pos.distance(ofVec3f(ofGetWidth() / 2, ofGetHeight() / 2, 0));
	ofDrawSphere(pos, 40 * pow(dis,-0.45));
}

void pathObj::mirrorDraw(float t)
{
	float m = t / 200.0;
	ofSetColor((200 - t / 2) * m, (80 - t / 6)* m , (int(t * 10) % 255) * m);
	float dis = pos.distance(ofVec3f(ofGetWidth() / 2, ofGetHeight() / 2, 0));
	ofDrawSphere(pos, 40 * pow(dis, -0.45));

}
void pathObj::drawFade(float t, int isMirror)
{
	
	float dis = pos.distance(ofVec3f(ofGetWidth() / 2, ofGetHeight() / 2, 0));
	float f = pow(t/200+0.5, -4);// fade weight
	switch(isMirror)
	{
	case 1:
		if (t < 164) ofSetColor((200 - t / 2) * f, (80 - t / 6) * f, (int(t * 10) % 255) * f);
		else ofSetColor(0);
		ofDrawSphere(pos, 40 * pow(dis, -0.45));
		break;
	case 2:
		if (t < 164) ofSetColor(min((180.0f - t / 2.0f) * f,0.0f), min((70 - t / 6.0f) * f,0.0f), min((int(t * 10) - 10 % 255) * f,0.0f));
		else ofSetColor(0);
		ofDrawSphere(pos, 40 * pow(dis, -0.45));
		break;
	}
	
}
void pathObj::drawEnd(float t, int count)
{
	ofSetColor((200 - t / 2), (80 - t / 6), (int(t * 10) % 255));
	float dis = pos.distance(ofVec3f(ofGetWidth() / 2, ofGetHeight() / 2, pos.z));
	ofVec3f vec = (pos- ofVec3f(ofGetWidth() / 2, ofGetHeight() / 2, pos.z))*ofVec3f(count/6.0f*(t / 200) * (t / 200));
	/*cout << "pos.z:" << count / 120.0f << endl;
	cout << "count / 120.0f:" << count / 120.0f << endl;*/
	
	ofDrawSphere(pos+vec, 40 * pow(dis, -0.45));
}










//Now come the randomObjects!

randomObj::randomObj()
{
	this->pos = ofVec3f(ofRandom(500), ofRandom(500));
	this->vel = ofVec3f(ofRandom(1), ofRandom(1));

	this->appealWeight = 1.4;
	this->repelWeight = 0.4;
	this->appealHood = 1800;
	this->repelHood = 60;
}

randomObj::randomObj(ofVec3f posIn, ofVec3f velIn, float aW, float rW, float aH, float rH)
{
	this->pos = posIn;
	this->vel = velIn;
	this->appealWeight = aW;
	this->repelWeight = rW;
	this->appealHood = aH;
	this->repelHood = rH;
}

//randomObj::~randomObj()
//{
//}

void randomObj::setPos(ofVec3f p)
{
	this->pos = p;
}

void randomObj::setVel(ofVec3f v)
{
	this->vel = v;
}

void randomObj::setAppealHood(float aH)
{
	this->appealHood = aH;
}

void randomObj::setRepelHood(float rH)
{
	this->appealHood = rH;
}

ofVec3f randomObj::getPos()
{
	return this->pos;
}

ofVec3f randomObj::getVel()
{
	return this->vel;
}

float randomObj::getAppealHood()
{
	return this->appealHood;
}

float randomObj::getRepelHood()
{
	return this->repelHood;
}


ofVec3f randomObj::appeal(pathObj* otherObj)
{
	ofVec3f v(0, 0, 0);
	if (pos.distance(otherObj->getPos()) < appealHood)
	{
		v = otherObj->getPos() - pos;
	}
	
	v.normalize();
	return v;
};


ofVec3f randomObj::appeal(vector < pathObj*>& otherObj)
{
	ofVec3f average(0, 0, 0);
	int count = 0;
	for (unsigned int i = 0; i < otherObj.size(); i++)
	{
		if (pos.distance(otherObj[i]->getPos()) < appealHood)
		{
			average += otherObj[i]->getPos();
			count += 1;//count =  count + 1;
		}
	}
	average /= count;
	ofVec3f v = average - pos;
	v.normalize();
	return v;
};

ofVec3f randomObj::repel(pathObj* otherObj)
{
	ofVec3f v(0, 0, 0);
	if (pos.distance(otherObj->getPos()) < repelHood)
	{
		v = pos - otherObj->getPos();
	}
	v.normalize();
	return v;
};


ofVec3f randomObj::repel(vector < pathObj*> & otherObj)
{
	return ofVec3f();
};

void randomObj::update(pathObj* otherObj, float t)
{
	vel += repel(otherObj) * repelWeight;
	vel += appeal(otherObj) * appealWeight;
	pos += vel;

	float para = 0.4;
	vel.x = pos.x > ofGetWidth() ? -vel.x * para : vel.x;//Three-Issue-Structure to take place of the Walls-Function
	vel.x = pos.x < FLT_MIN ? -vel.x * para : vel.x;
	vel.y = pos.y > ofGetHeight() ? -vel.y * para : vel.y;
	vel.y = pos.y < FLT_MIN ? -vel.y * para : vel.y;

	distance = pos.distance(otherObj->getPos());
};

void randomObj::update(vector < pathObj*> & otherObj, float t)
{
	vel += repel(otherObj)*repelWeight;
	vel += appeal(otherObj)*appealWeight;
	pos += vel;
};

void randomObj::draw(float t)
{
	ofSetColor(int(t * 5) % 255, max(180 - distance / 3,0.0f), max(200 - distance / 3,0.0f),200);
	ofDrawSphere(pos, max(0.1, 2.0 - distance / 200));
}
