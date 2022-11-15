#pragma once
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <OgreMeshManager.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreFrameListener.h>
#include <OgreAnimation.h>
#include <OgreKeyFrame.h>
#include <iostream>
#include <OgreTimer.h>
#include <OgreBillboardSet.h>
using namespace Ogre;
enum MessageType{DEFAULT, EXPLOSION};
class EntidadIG :public OgreBites::InputListener {
public:
	//Constructora y destructora
	EntidadIG();
	~EntidadIG();
	//Vector estático de listeners
	static std::vector<EntidadIG*> appListeners;
	//Añadir entidad como listener al vector con push_back()
	static void addListener(EntidadIG* entidad) { appListeners.push_back(entidad); }
	virtual void frameRendered(const Ogre::FrameEvent& evt) {}
	void sendEvent(MessageType msgType, EntidadIG* entidad);
	virtual void receiveEvent(MessageType msgType, EntidadIG* entidad) {};
protected:
	Ogre::SceneNode* mNode = nullptr;
	Ogre::SceneManager* mSM = nullptr;
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt)
	{
		return false;
	};
};

