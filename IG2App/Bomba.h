#pragma once
#include "EntidadIG.h"
class Bomba:public EntidadIG
{
public:
	Bomba(SceneNode* node);
	~Bomba(){}
	virtual void frameRendered(const Ogre::FrameEvent& evt);
	virtual void receiveEvent(MessageType msgType, EntidadIG* entidad);
protected:
	AnimationState* animationState;
};

