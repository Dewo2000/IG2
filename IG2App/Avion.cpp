#include "Avion.h"

Avion::Avion(SceneNode* node)
{
	mNode = node;
	mSM = mNode->getCreator();
	Entity* ent = mSM->createEntity("sphere.mesh");
	ent->setMaterialName("Practica1/Rojo");
	mNode->createChildSceneNode("CabezaAvion")->attachObject(ent);
	//mSM->getSceneNode("CabezaAvion")->setScale({ 10,10,10 });
	ent = mSM->createEntity("Barrel.mesh");
	ent->setMaterialName("Practica1/Naranjon");
	mNode->createChildSceneNode("Morro")->attachObject(ent);
	mSM->getSceneNode("Morro")->setScale({ 10,3,10 });
	mSM->getSceneNode("Morro")->setPosition({ 0,0,100 });
	mSM->getSceneNode("Morro")->pitch(Degree(90));

	ent = mSM->createEntity("ninja.mesh");
	ent->setMaterialName("Practica1/Amarillo");
	mNode->createChildSceneNode("PilotoNinja")->attachObject(ent);
	mSM->getSceneNode("PilotoNinja")->setScale({ 0.6,0.6,0.6 });
	mSM->getSceneNode("PilotoNinja")->setPosition({ 0,20,0 });
	mSM->getSceneNode("PilotoNinja")->yaw(Degree(180));

	ent = mSM->createEntity("cube.mesh");
	ent->setMaterialName("Practica1/checker");
	mNode->createChildSceneNode("Ala1")->attachObject(ent);
	mSM->getSceneNode("Ala1")->setScale({ 2,0.1,1 });
	mSM->getSceneNode("Ala1")->setPosition({ 150,0,0 });

	ent = mSM->createEntity("cube.mesh");
	ent->setMaterialName("Practica1/checker");
	mNode->createChildSceneNode("Ala2")->attachObject(ent);
	mSM->getSceneNode("Ala2")->setScale({ 2,0.1,1 });
	mSM->getSceneNode("Ala2")->setPosition({ -150,0,0 });

	aspanave1 = new AspasNave(mNode->createChildSceneNode("AspaNave1"), "AspaNave1", 5);
	mSM->getSceneNode("AspaNave1")->setScale({ 0.25,0.25,0.25 });
	mSM->getSceneNode("AspaNave1")->setPosition({ 180,0,50 });
	aspanave2 = new AspasNave(mNode->createChildSceneNode("AspaNave2"), "AspaNave2", 5);
	mSM->getSceneNode("AspaNave2")->setScale({ 0.25,0.25,0.25 });
	mSM->getSceneNode("AspaNave2")->setPosition({ -180,0,50 });

	BillboardSet* bbSet = mSM->createBillboardSet("AvionBS", 1);
	bbSet->setDefaultDimensions(100, 60);
	bbSet->setMaterialName("Practica1/10points");
	mNode->attachObject(bbSet);
	Billboard* bb = bbSet->createBillboard(Vector3(0, 0, -150));
}

void Avion::frameRendered(const Ogre::FrameEvent& evt)
{
	mNode->translate(300, 0, 0, SceneNode::TS_LOCAL);
	mNode->yaw(Ogre::Degree(2));
	mNode->translate(-300, 0, 0, SceneNode::TS_LOCAL);

	aspanave1->girarAspas();
	aspanave2->girarAspas();
}
