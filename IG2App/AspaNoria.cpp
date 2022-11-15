#include "AspaNoria.h"

AspaNoria::AspaNoria(SceneNode* node, int id, float angle)
{
	mNode = node;
	mSM = mNode->getCreator();
	Entity* ent = mSM->createEntity("cube.mesh");
	ent->setMaterialName("Practica1/Marron");
	std::string nameTab1 = "Tablero1 " + std::to_string(id);
	mNode->createChildSceneNode(nameTab1)->attachObject(ent);
	mSM->getSceneNode(nameTab1)->setScale(10, 0.5, 0.2);
	mSM->getSceneNode(nameTab1)->setPosition(0, 0, 50);
	ent = mSM->createEntity("cube.mesh");
	ent->setMaterialName("Practica1/Marron");
	std::string nameTab2 = "Tablero2 " + std::to_string(id);
	mNode->createChildSceneNode(nameTab2)->attachObject(ent);
	mSM->getSceneNode(nameTab2)->setScale(10, 0.5, 0.2);
	mSM->getSceneNode(nameTab2)->setPosition(0, 0, -50);
	ent = mSM->createEntity("cube.mesh");
	ent->setMaterialName("Practica1/Cubo");
	std::string nameCubo = "Cubo " + std::to_string(id);
	mNode->createChildSceneNode(nameCubo)->attachObject(ent);
	mSM->getSceneNode(nameCubo)->setPosition(500, 0, 0);
	mSM->getSceneNode(nameCubo)->roll(Radian(-angle)); // colocamos la cabina en horizontal
}

AspaNoria::~AspaNoria()
{
}



