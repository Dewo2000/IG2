#include "Bomba.h"

Bomba::Bomba(SceneNode* node)
{
	mNode = node;
	mSM = mNode->getCreator();
	Entity* ent = mSM->createEntity("uv_sphere.mesh");
	ent->setMaterialName("IG2/bomba2");
	//Entity* ent = mSM->createEntity("Barrel.mesh");
	//ent->setMaterialName("Practica1/checker");
	mNode->attachObject(ent);
	//mNode->setScale(10, 10, 10);
	mNode->setInitialState();
	

	double duracion = 4.0, desplazamiento = 250.0;
	Animation* animation = mSM->createAnimation("animVV", duracion);
	NodeAnimationTrack* track = animation->createNodeTrack(0);
	track->setAssociatedNode(mNode);
	Vector3 keyframePos0(0., 0., 0.); // Posicion inicial
	Vector3 src(0, 0, 1); // Rotacion inicial
	Vector3 keyframePos = keyframePos0;
	Real durPaso = duracion / 4.0;
	TransformKeyFrame* kf; // 5 keyFrames: origen(0), arriba, origen, abajo, origen(4)
	kf = track->createNodeKeyFrame(durPaso * 0); // Keyframe 0: origen
	kf->setTranslate(keyframePos); // Origen: Vector3
	kf = track->createNodeKeyFrame(durPaso * 1); // Keyframe 1: arriba
	keyframePos = keyframePos0 + Ogre::Vector3::UNIT_Y * desplazamiento;
	kf->setTranslate(keyframePos); // Arriba
	kf->setRotation(src.getRotationTo(Vector3(1, 0, 1))); // Yaw(45) 
	kf = track->createNodeKeyFrame(durPaso * 2); // Keyframe 2: origen
	keyframePos = keyframePos0;
	kf->setTranslate(keyframePos); // Origen
	kf = track->createNodeKeyFrame(durPaso * 3); // Keyframe 3: abajo
	keyframePos = keyframePos0 - Ogre::Vector3::UNIT_Y * desplazamiento;
	kf->setTranslate(keyframePos); // Abajo
	kf->setRotation(src.getRotationTo(Vector3(-1, 0, 1))); // Yaw(-45)
	kf = track->createNodeKeyFrame(durPaso * 4); // Keyframe 4: origen
	keyframePos = keyframePos0;
	kf->setTranslate(keyframePos); // Origen
	animationState = mSM->createAnimationState("animVV");
	animationState->setLoop(true);
	animationState->setEnabled(true);


	pSysExplode = mSM->createParticleSystem("psBombaExplode", "IG2App/BarrelExplode");
	pSysExplode->setEmitting(false);
	mNode->createChildSceneNode("psyBombaExplode")->attachObject(pSysExplode);
}

void Bomba::frameRendered(const Ogre::FrameEvent& evt)
{
	if(!exploted)
	animationState->addTime(evt.timeSinceLastFrame);
}

void Bomba::receiveEvent(MessageType msgType, EntidadIG* entidad)
{
	if (msgType == STOP) {
		animationState->setEnabled(false);
	
	}
	else if (msgType == SIMBAD_DIE) {
		explode();
	}
}

void Bomba::explode()
{
	exploted = true;
	pSysExplode->setEmitting(true);
	pSysExplode->getEmitter(0)->setDuration(1);
	mNode->setVisible(false);
	mSM->getSceneNode("psyBombaExplode")->setVisible(true);
}
