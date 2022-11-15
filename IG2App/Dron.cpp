#include "Dron.h"
#include "BrazoDron.h"
#include <random>
Dron::Dron(SceneNode* node,int numbrazo,int id, bool esAvispa)
{
	std::string thisID = std::to_string(numbrazo + id);
	this->thisID = thisID;
	mNode = node;
	avispa = esAvispa;
	mSM = mNode->getCreator();
	myEnt = mSM->createEntity("sphere.mesh");
	if (esAvispa)myEnt->setMaterialName("Practica1/MunecoCabeza");
	else myEnt->setMaterialName("Practica1/Rojo");
	mNode->createChildSceneNode("CabezaDron"+ thisID)->attachObject(myEnt);
	myTimer = new Ogre::Timer();
	time = myTimer->getMilliseconds();
	gira = false;
	//mSM->getSceneNode("CabezaAvion")->setScale({ 10,10,10 });

	this->numbrazo = numbrazo;
	double r = 220;
	for (int i = 0; i < numbrazo; i++) {
		BrazoDron* bd;
		std::string name = "Brazo " + std::to_string(i + 1) + thisID;
		mNode->createChildSceneNode(name);
		float ang = (i / (double)numbrazo * 2 * Math::PI);
		mSM->getSceneNode(name)->setPosition(Math::Cos(ang) * r, Math::Sin(ang) * r, 0.0);
		mSM->getSceneNode(name)->setScale(0.5,0.5,0.5);
		mSM->getSceneNode(name)->roll(Radian(ang));
		bd = new BrazoDron(mSM->getSceneNode(name), name);
	}
	mSM->getSceneNode("Brazo 1" + thisID)->setPosition(Math::Cos(0) * (r + 40), Math::Sin(0) * (r + 20), 0.0);
	if (esAvispa)mNode->setScale(0.5, 0.5, 0.5);
}

void Dron::frameRendered(const Ogre::FrameEvent& evt){

	long t = myTimer->getMilliseconds();
	
	if (time + 2000 > t) {
		mNode->translate(0, 0, -305, SceneNode::TS_LOCAL);
		mNode->yaw(Ogre::Degree(2));
		mNode->translate(0, 0, 305, SceneNode::TS_LOCAL);
	}
	else
	{
		if (!gira) {
			gira = true;
			stoptime = t + rand() % 2000;
			dir = rand() % 2;
		}
		else if(stoptime < t)
		{
			time = t;
			gira = false;
		}
	}
	if (gira)
	{

		if (dir == 0) {
			mNode->roll(Ogre::Degree(-5));
		}
		else
		{
			mNode->roll(Ogre::Degree(5));
		}
	}
	moverAspas();
}

void Dron::changeColor()
{
	//Ogre::Entity* ent = (Ogre::Entity*)mSM->getSceneNode("CabezaDron" + thisID)->getAttachedObject("CabezaDron" + thisID);
	myEnt->setMaterialName("Practica1/Amarillo");
}

void Dron::moverAspas()
{
	for (int i = 0; i < numbrazo; i++) {
		std::string name = "Brazo " + std::to_string(i + 1) + thisID;
		mSM->getSceneNode(name)->getChild("BrazoAspa" + name)->roll(Degree(5));
	}
}
