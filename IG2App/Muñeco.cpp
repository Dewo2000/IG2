#include "Muñeco.h"

Muñeco::Muñeco(SceneNode* node)
{
	mNode = node;
	mSM = mNode->getCreator();

	Ogre::Entity* ent = mSM->createEntity("Cabeza", "sphere.mesh");
	ent->setMaterialName("Practica1/MunecoCabeza");
	mNode->createChildSceneNode("Cabeza")->attachObject(ent);
	mSM->getSceneNode("Cabeza")->setPosition(0, 150, 0);
	mSM->getSceneNode("Cabeza")->setScale(0.6, 0.6, 0.6);
	

	ent = mSM->createEntity("Cuerpo","sphere.mesh");
	ent->setMaterialName("Practica1/MunecoCuerpo");
	mNode->createChildSceneNode("Cuerpo")->attachObject(ent);
	ent = mSM->createEntity("sphere.mesh");
	ent->setMaterialName("Practica1/Rojo");
	mSM->getSceneNode("Cuerpo")->createChildSceneNode("Ombligo")->attachObject(ent);
	mSM->getSceneNode("Ombligo")->setPosition(0, 0, 100);
	mSM->getSceneNode("Ombligo")->setScale(0.2, 0.2, 0.2);
	mNode->setInitialState();

	// Animacion cambiar de plataforma
	double duracion = 12.0;
	Animation* animation = mSM->createAnimation("MovePlatform", duracion);
	NodeAnimationTrack* track = animation->createNodeTrack(0);
	track->setAssociatedNode(mNode);
	Vector3 keyframePos0(0, 0, 0); // Posicion inicial
	Vector3 keyframePos = keyframePos0; //= keyframePos0;
	TransformKeyFrame* kf; // 7 keyFrames:
	// Keyframe 0: origen
	kf = track->createNodeKeyFrame(0.0);
	kf->setTranslate(keyframePos); // Origen: Vector3
	// Keyframe 1: 
	kf = track->createNodeKeyFrame(1.0);
	Quaternion q1 = Quaternion(Degree(-90.0), Vector3(0, 1, 0));
	kf->setRotation(q1); // Yaw(-90) 
	// Keyframe 2:
	kf = track->createNodeKeyFrame(5.0);
	keyframePos = Vector3(-250, 0, 0);
	kf->setRotation(q1);
	kf->setTranslate(keyframePos);
	// Keyframe 3:
	kf = track->createNodeKeyFrame(7.0);
	q1 = Quaternion(Degree(90.0), Vector3(0, 1, 0));
	kf->setRotation(q1); // Yaw(180)
	kf->setTranslate(keyframePos);
	// Keyframe 4:
	kf = track->createNodeKeyFrame(11.0);
	keyframePos = keyframePos0;
	kf->setRotation(q1);
	kf->setTranslate(keyframePos);
	// Keyframe 5:
	kf = track->createNodeKeyFrame(12.0);
	q1 = Quaternion(Degree(0.0), Vector3(0, 1, 0));
	kf->setRotation(q1); // Yaw(-90)
	kf->setTranslate(keyframePos);
	animationState = mSM->createAnimationState("MovePlatform");
	animationState->setLoop(true);
	animationState->setEnabled(true);

}

Muñeco::~Muñeco()
{
}

void Muñeco::receiveEvent(MessageType msgType, EntidadIG* entidad)
{
	active = !active;
	if (active)
	{
		Ogre::Entity* ent = (Ogre::Entity*)mSM->getSceneNode("Cabeza")->getAttachedObject("Cabeza");
		ent->setMaterialName("Practica1/MunecoCabezaR");
		ent = (Ogre::Entity*)mSM->getSceneNode("Cuerpo")->getAttachedObject("Cuerpo");
		ent->setMaterialName("Practica1/MunecoCuerpoR");
	}
	else {
		Ogre::Entity* ent = (Ogre::Entity*)mSM->getSceneNode("Cabeza")->getAttachedObject("Cabeza");
		ent->setMaterialName("Practica1/MunecoCabeza");
		ent = (Ogre::Entity*)mSM->getSceneNode("Cuerpo")->getAttachedObject("Cuerpo");
		ent->setMaterialName("Practica1/MunecoCuerpo");
	}
}

void Muñeco::frameRendered(const Ogre::FrameEvent& evt)
{
	animationState->addTime(evt.timeSinceLastFrame);
}

bool Muñeco::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	Vector3 pos = mNode->getPosition();
	Radian angle = mNode->getOrientation().getYaw();
	float dist = 5.0f;
	if (evt.keysym.sym == SDLK_UP)
	{
		mNode->setPosition(pos.x+Math::Sin(angle)*dist, pos.y, pos.z+ Math::Cos(angle) * dist);
	}
	else if (evt.keysym.sym == SDLK_DOWN) {
		mNode->setPosition(pos.x - Math::Sin(angle) * dist, pos.y, pos.z - Math::Cos(angle) * dist);
	}
	else if (evt.keysym.sym == SDLK_LEFT) {
		mNode->yaw(Degree(5));
	}
	else if (evt.keysym.sym == SDLK_RIGHT) {
		mNode->yaw(Degree(-5));
	}
	return true;
}
