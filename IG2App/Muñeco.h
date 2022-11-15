#pragma once
#include "EntidadIG.h"
class Muñeco: public EntidadIG
{
public:
	Muñeco(SceneNode* node);
	~Muñeco();
	virtual void receiveEvent(MessageType msgType, EntidadIG* entidad);
	virtual void frameRendered(const Ogre::FrameEvent& evt);
protected:
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	bool active = false;
	AnimationState* animationState;
};

