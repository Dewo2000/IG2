#pragma once
#include "EntidadIG.h"
class Plano: public EntidadIG
{
public:
	Plano(SceneNode* node);
	~Plano();
	virtual void receiveEvent(MessageType msgType, EntidadIG* entidad);
	virtual void frameRendered(const Ogre::FrameEvent& evt);
protected:
	Entity* entPlane;
	Ogre::Timer* myTimer;
	bool active = true, messageReceived = false;
	long time;
};

