#pragma once
#include "EntidadIG.h"
class Bomba:public EntidadIG
{
public:
	Bomba(SceneNode* node);
	~Bomba(){}
	virtual void frameRendered(const Ogre::FrameEvent& evt);
	virtual void receiveEvent(MessageType msgType, EntidadIG* entidad);
	void explode();
protected:
	AnimationState* animationState;
	ParticleSystem* pSysExplode;
};

