#pragma once
#include "EntidadIG.h"
class Mu�eco: public EntidadIG
{
public:
	Mu�eco(SceneNode* node);
	~Mu�eco();
	virtual void receiveEvent(MessageType msgType, EntidadIG* entidad);
	virtual void frameRendered(const Ogre::FrameEvent& evt);
protected:
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	bool active = false;
	AnimationState* animationState;
};

