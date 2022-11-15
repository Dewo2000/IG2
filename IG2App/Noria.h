#pragma once
#include "EntidadIG.h"
#include "AspaNoria.h"
class Noria : public EntidadIG
{
public:
	Noria(SceneNode* node, int numAspas);
	~Noria();
	virtual void frameRendered(const Ogre::FrameEvent& evt);
	virtual void receiveEvent(MessageType msgType, EntidadIG* entidad);
protected:
	int numAspas;
	bool active = true;
};

