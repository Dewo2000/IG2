#include "Noria.h"

Noria::Noria(SceneNode* node, int numAspas_)
{
	mNode = node;
	mSM = mNode->getCreator();
	Entity* ent = mSM->createEntity("Barrel.mesh");
	ent->setMaterialName("Practica1/Cilindro");
	mNode->createChildSceneNode("Cilindro")->attachObject(ent);
	mSM->getSceneNode("Cilindro")->pitch(Degree(90));
	mSM->getSceneNode("Cilindro")->setScale({ 10,10,10 });

	SceneNode* nodoAspas = mNode->createChildSceneNode("Aspas");
	numAspas = numAspas_;
	double r = 500;
	for (int i = 0; i < numAspas; i++) {
		AspaNoria* aspa;
		std::string name = "Aspa " + std::to_string(i + 1);
		nodoAspas->createChildSceneNode(name);
		float ang = (i / (double)numAspas * 2 * Math::PI);
		mSM->getSceneNode(name)->setPosition(Math::Cos(ang) * r, Math::Sin(ang) * r, 0.0);
		mSM->getSceneNode(name)->roll(Radian(ang));
		aspa = new AspaNoria(mSM->getSceneNode(name), i + 1, ang);
	}
	mSM->getSceneNode("Aspas")->setScale( 0.3, 0.3, 0.3 );
	
}

Noria::~Noria()
{
}



void Noria::frameRendered(const Ogre::FrameEvent& evt)
{
	if (active) {
		float angle = 0.5;
		mSM->getSceneNode("Aspas")->roll(Degree(angle));
		// Se deshace la rotacion de la cabina
		for (int i = 0; i < numAspas; i++) {
			std::string nameCubo = "Cubo " + std::to_string(i + 1);
			mSM->getSceneNode(nameCubo)->roll(Degree(-angle));
		}
	}
	
}

void Noria::receiveEvent(MessageType msgType, EntidadIG* entidad)
{
	if(msgType==DEFAULT)
	active = !active;
}
