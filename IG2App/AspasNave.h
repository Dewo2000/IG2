#pragma once
#include "EntidadIG.h"
class AspasNave: public EntidadIG
{
public:
	AspasNave(SceneNode* node , std::string id ,int numAspas);
	~AspasNave(){};
	virtual void receiveEvent(MessageType msgType, EntidadIG* entidad);
	//virtual void frameRendered(const Ogre::FrameEvent& evt);
	void girarAspas();
protected:
	//virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	bool active = false;
	int numAspas;
	SceneNode* nodoAspas;
};

