#pragma once
#include "EntidadIG.h"
#include "AspasNave.h"
class Avion : public EntidadIG
{
public:
	Avion(SceneNode* node);
	~Avion() {};
	virtual void frameRendered(const Ogre::FrameEvent& evt);
	void explode();
protected:
	AspasNave* aspanave1, * aspanave2;
	ParticleSystem* pSysExplode;
};

