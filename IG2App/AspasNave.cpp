#include "AspasNave.h"
#include "Aspa.h"

AspasNave::AspasNave(SceneNode* node, std::string id,int numAspas)
{
	mNode = node;
	mSM = mNode->getCreator();
	std::string name = "AspasNave" + id;
	Entity* ent = mSM->createEntity("Barrel.mesh");
	ent->setMaterialName("Practica1/dirt01");
	mNode->createChildSceneNode(name)->attachObject(ent);
	mSM->getSceneNode(name)->setScale({ 8,4,8 });
	mSM->getSceneNode(name)->pitch(Degree(90));
	

	nodoAspas = mNode->createChildSceneNode("Aspas" + id);
	this->numAspas = numAspas;
	double r = 350;
	for (int i = 0; i < numAspas; i++) {
		Aspa* aspa;
		std::string name = "Aspa" + std::to_string(i + 1) +id;
		nodoAspas->createChildSceneNode(name);
		float ang = (i / (double)numAspas * 2 * Math::PI);
		mSM->getSceneNode(name)->setPosition(Math::Cos(ang) * r, Math::Sin(ang) * r, 0.0);
		mSM->getSceneNode(name)->roll(Radian(ang));
		aspa = new Aspa(mSM->getSceneNode(name), name + std::to_string(i + 1), ang);
	}
	mSM->getSceneNode("Aspas" + id)->setScale(0.3, 0.3, 0.3);

}

void AspasNave::receiveEvent(MessageType msgType, EntidadIG* entidad)
{
}

void AspasNave::girarAspas()
{
	nodoAspas->roll(Degree(5));
}
