#include "BrazoDron.h"
#include "AspasNave.h"
void BrazoDron::girarAspa()
{
	mSM->getSceneNode(aspaName)->roll(Degree(5));
}
BrazoDron::BrazoDron(SceneNode* node, string fname)
{
	mNode = node;
	mSM = mNode->getCreator();
	std::string name = "BrazoCilindro" + fname;
	Entity* ent = mSM->createEntity("Barrel.mesh");
	ent->setMaterialName("Practica1/BrazoDron");
	mNode->createChildSceneNode(name)->attachObject(ent);
	mSM->getSceneNode(name)->setScale({ 18,40,18 });
	mSM->getSceneNode(name)->setPosition({ -210,0,0 });
	mSM->getSceneNode(name)->roll(Degree(90));

	name = "BrazoEsfera" + fname;
	ent = mSM->createEntity("sphere.mesh");
	ent->setMaterialName("Practica1/Naranjon");
	mNode->createChildSceneNode(name)->attachObject(ent);
	//mSM->getSceneNode(name)->setScale({ 0.2,0.2,0.2 });


	AspasNave* aspanave1 = new AspasNave(mNode->createChildSceneNode("BrazoAspa"+fname), fname, 3);
	mSM->getSceneNode("BrazoAspa" + fname)->setScale({ 0.35,0.35,0.35 });
	mSM->getSceneNode("BrazoAspa" + fname)->setPosition({ 0,0,100 });
	aspaName = "BrazoAspa" + fname;
}
