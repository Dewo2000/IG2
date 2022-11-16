#include "Sinbad.h"

Sinbad::Sinbad(SceneNode* node)
{
	mNode = node;
	mSM = mNode->getCreator();

	sinbadEnt = mSM->createEntity("Sinbad.mesh");
	mNode->createChildSceneNode("nSinbad")->attachObject(sinbadEnt);


	AnimationState* runBase = sinbadEnt->getAnimationState("RunBase");
	runBase->setEnabled(true);
	runBase->setLoop(true);
	vAnimations.push_back(runBase);
	AnimationState* runTop = sinbadEnt->getAnimationState("RunTop");
	runTop->setEnabled(true);
	runTop->setLoop(true);
	vAnimations.push_back(runTop);
	AnimationState* dance = sinbadEnt->getAnimationState("Dance");
	dance->setEnabled(false);
	dance->setLoop(true);
	vAnimations.push_back(dance);

	AnimationStateSet* set = sinbadEnt->getAllAnimationStates();
	auto it = set->getAnimationStateIterator().begin();
	while (it != set->getAnimationStateIterator().end()) {
		auto s = it->first;
		++it;
		std::cout << s << "\n";
	}
	myTimer = new Ogre::Timer();
	time = myTimer->getMilliseconds();

	rightSword = mSM->createEntity("Sword.mesh");
	leftSword = mSM->createEntity("Sword.mesh");

	
}

void Sinbad::receiveEvent(MessageType msgType, EntidadIG* entidad)
{
	if (msgType == PLANE_EXPLOTION && !died) {
		died = true;
		diemsg = true;
		diemsgcount = myTimer->getMilliseconds();
		die();
	}
}

void Sinbad::frameRendered(const Ogre::FrameEvent& evt)
{
	for (AnimationState* a : vAnimations) {
		 a->addTime(evt.timeSinceLastFrame);
	}
	if (!isStatic && !dancing) {
		long t = myTimer->getMilliseconds();
		if (time + 2000 < t) {
			time = t;
			int degree = rand() % 180 - 90;
			mNode->yaw(Ogre::Degree(degree));
		}
		mNode->translate(0, -350, 0, SceneNode::TS_LOCAL);
		mNode->pitch(Ogre::Degree(2));
		mNode->translate(0, 350, 0, SceneNode::TS_LOCAL);
	}
	if (diemsg && diemsgcount+5000< myTimer->getMilliseconds()) {
		sendEvent(SIMBAD_DIE, this);
		diemsg = false;
	}
}

void Sinbad::arma(bool b)
{
	
	if (b && !rightSword->isAttached()) {
		sinbadEnt->attachObjectToBone("Handle.R", rightSword);
	}
	else {
		sinbadEnt->detachObjectFromBone(leftSword);
		sinbadEnt->detachObjectFromBone(rightSword);
	}
}

void Sinbad::arma()
{
	if(!rightSword->isAttached())
	sinbadEnt->attachObjectToBone("Handle.R", rightSword);
	if (!leftSword->isAttached())
	sinbadEnt->attachObjectToBone("Handle.L", leftSword);
}

void Sinbad::cambiaEspada()
{
	if (leftSword->isAttached() && !rightSword->isAttached()) {
		sinbadEnt->detachObjectFromBone(leftSword);
		sinbadEnt->attachObjectToBone("Handle.R", rightSword);
	}
	else if(!leftSword->isAttached() && rightSword->isAttached()) {
		sinbadEnt->detachObjectFromBone(rightSword);
		sinbadEnt->attachObjectToBone("Handle.L", leftSword);
	}
}

void Sinbad::danceOrGo()
{
	if (!dancing) {
		vAnimations[0]->setEnabled(false);
		vAnimations[1]->setEnabled(false);
		vAnimations[2]->setEnabled(true);
		dancing = true;
	}
	else {
		dancing = false;
		vAnimations[0]->setEnabled(true);
		vAnimations[1]->setEnabled(true);
		vAnimations[2]->setEnabled(false);
	}
}

void Sinbad::die()
{
	for (AnimationState* a : vAnimations)a->setEnabled(false);
	mNode->setInitialState();
	double duracion = 1.0;
	Animation* animation = mSM->createAnimation("SimbadDie", duracion);
	NodeAnimationTrack* track = animation->createNodeTrack(0);
	track->setAssociatedNode(mNode);
	Vector3 keyframePos(0, 0, 0);
	TransformKeyFrame* kf; 

	kf = track->createNodeKeyFrame(0.0);
	kf->setTranslate(keyframePos); 

	kf = track->createNodeKeyFrame(1.0);
	Quaternion q1 = Quaternion(Degree(-90), Vector3(1, 0, 0));
	kf->setRotation(q1);
	keyframePos = Vector3(0, -30, 0);
	kf->setTranslate(keyframePos);

	AnimationState* sinbaddie = mSM->createAnimationState("SimbadDie");
	sinbaddie->setEnabled(true);
	sinbaddie->setLoop(false);
	vAnimations.push_back(sinbaddie);
	arma(false);

	/*AnimationState* IdleTop = sinbadEnt->getAnimationState("IdleTop");
	IdleTop->setEnabled(true);
	vAnimations.push_back(IdleTop);
	AnimationState* IdleBase = sinbadEnt->getAnimationState("IdleBase");
	IdleBase->setEnabled(true);
	vAnimations.push_back(IdleBase);*/
}

void Sinbad::setRunAnimation()
{
	mNode->setInitialState();
	// Animacion cambiar de plataforma
	double duracion = 12.0;
	Animation* animation = mSM->createAnimation("ChangePlatform", duracion);
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
	Quaternion q1 = Quaternion(Degree(120.0), Vector3(0, 1, 0));
	kf->setRotation(q1); // Yaw(120) 
	// Keyframe 2:
	kf = track->createNodeKeyFrame(5.0); 
	keyframePos = Vector3(600, 0, -600);
	kf->setRotation(q1);
	kf->setTranslate(keyframePos);
	// Keyframe 3:
	kf = track->createNodeKeyFrame(6.0); 
	q1 = Quaternion(Degree(0.0), Vector3(0, 1, 0));
	kf->setRotation(q1); // Yaw(120)
	kf->setTranslate(keyframePos);
	// Keyframe 4:
	kf = track->createNodeKeyFrame(7.0); 
	q1 = Quaternion(Degree(-30.0), Vector3(0, 1, 0));
	kf->setRotation(q1); // Yaw(30)
	kf->setTranslate(keyframePos);
	// Keyframe 5:
	kf = track->createNodeKeyFrame(11.0); 
	keyframePos = keyframePos0;
	kf->setRotation(q1);
	kf->setTranslate(keyframePos); // Origen
	// Keyframe 6:
	kf = track->createNodeKeyFrame(12.0); 
	q1 = Quaternion(Degree(0.0), Vector3(0, 1, 0));
	kf->setRotation(q1); // Yaw(-30)
	kf->setTranslate(keyframePos);
	AnimationState* animationState = mSM->createAnimationState("ChangePlatform");
	animationState->setLoop(true);
	animationState->setEnabled(true);
	vAnimations.push_back(animationState);
}
