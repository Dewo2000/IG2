#pragma once
#include "EntidadIG.h"
class Dron : public EntidadIG
{
public:
	Dron(SceneNode* node,int numbrazo,int id, bool esAvispa);
	~Dron() {};
	virtual void frameRendered(const Ogre::FrameEvent& evt);
	void changeColor();
protected:
	int numbrazo;
	bool avispa;
	void moverAspas();
	std::string thisID;
	Ogre::Timer* myTimer;
	long time , stoptime;
	bool gira;
	int dir;
	Entity* myEnt;
};

