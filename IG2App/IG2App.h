#ifndef __IG2App_H__
#define __IG2App_H__
#include <vector>
#include <iostream>
#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>
#include "AspaNoria.h"
#include "Noria.h"
#include "Muñeco.h"
#include "Plano.h"
#include "Avion.h"
#include "Dron.h"
#include "Sinbad.h"
#include "Bomba.h"



class IG2App : public  OgreBites::IG2ApplicationContext, OgreBites::InputListener 
{
public:
  explicit IG2App() : IG2ApplicationContext("IG2App") { };  // new -> setup()  
  virtual ~IG2App() { };   // delete -> shutdown()  
 
protected:
  virtual void setup();
  virtual void shutdown();
  virtual void setupScene();

  virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);  // InputListener
      
  Ogre::SceneManager* mSM = nullptr;
  OgreBites::TrayManager* mTrayMgr = nullptr;    
  Ogre::SceneNode* mLightNode = nullptr;
  Ogre::SceneNode* mCamNode = nullptr;
  Ogre::SceneNode* mSinbadNode = nullptr;
  OgreBites::CameraMan* mCamMgr = nullptr;

  AspaNoria* aspa = nullptr;
  Noria* noria = nullptr;
  Muñeco* muñeco = nullptr;
  Plano* plano = nullptr;
  Avion* avion = nullptr;
  Dron* dron = nullptr;

  Sinbad* sinbad = nullptr;
  Bomba* bomba = nullptr;

  std::vector<SceneNode*> dronVector;
  SceneNode* tierraFake;
  OgreBites::ParamsPanel* panel;
};

#endif
