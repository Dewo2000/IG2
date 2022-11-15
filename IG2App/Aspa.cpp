#include "Aspa.h"

Aspa::Aspa(SceneNode* node, std::string fname, float angle)
{
	mNode = node;
	mSM = mNode->getCreator();
	Entity* ent = mSM->createEntity("cube.mesh");
	ent->setMaterialName("Practica1/Marron");
	std::string nameTab1 = "Tablero1 " + fname;
	mNode->createChildSceneNode(nameTab1)->attachObject(ent);
	mSM->getSceneNode(nameTab1)->setScale(8, 1, 0.2);
	//mSM->getSceneNode(nameTab1)->setPosition(0, 0, 50);
	
	ent = mSM->createEntity("Barrel.mesh");
	ent->setMaterialName("Practica1/Rojo");
	std::string nameCubo = "Cilindro " + fname;
	mNode->createChildSceneNode(nameCubo)->attachObject(ent);
	mSM->getSceneNode(nameCubo)->setPosition(350, 0, 20);
	mSM->getSceneNode(nameCubo)->setScale(4, 12, 4);
	mSM->getSceneNode(nameCubo)->roll(Radian(-angle)); // colocamos la cabina en horizontal
}
