#pragma once
#include "EntidadIG.h"
#include <vector>
class Sinbad : public EntidadIG
{
public:
	Sinbad(SceneNode* node);
	~Sinbad(){};
	virtual void receiveEvent(MessageType msgType, EntidadIG* entidad);
	virtual void frameRendered(const Ogre::FrameEvent& evt);
	void arma(bool b);
	void arma();
	void cambiaEspada();
	void danceOrGo();
	void setStatic() { isStatic = true; }
	void die();
	void setRunAnimation();
protected:
	//AnimationState* animationState;
	//virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	bool active = false;
	bool dancing = false;
	bool isStatic = false;
	std::vector<AnimationState*> vAnimations;
	AnimationStateSet s;
	long time , diemsgcount;
	Ogre::Timer* myTimer;
	Entity* sinbadEnt, *rightSword,*leftSword;
	bool diemsg=false;
	bool died = false;
};
