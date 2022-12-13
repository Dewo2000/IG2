#include "IG2App.h"

#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include <OgreTimer.h>

using namespace Ogre;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt)
{
  if (evt.keysym.sym == SDLK_ESCAPE)
  {
    getRoot()->queueEndRendering();
  }
  return true;
}

void IG2App::shutdown()
{
  mShaderGenerator->removeSceneManager(mSM);  
  mSM->removeRenderQueueListener(mOverlaySystem);  
					
  mRoot->destroySceneManager(mSM);  

  delete mTrayMgr;  mTrayMgr = nullptr;
  delete mCamMgr; mCamMgr = nullptr;
  delete noria; noria = nullptr;
  delete plano; plano = nullptr;
  delete avion; avion = nullptr;
  // do not forget to call the base 
  IG2ApplicationContext::shutdown();
}

void IG2App::setup(void)
{
  // do not forget to call the base first
  IG2ApplicationContext::setup();

  mSM = mRoot->createSceneManager();  

  // register our scene with the RTSS
  mShaderGenerator->addSceneManager(mSM);

  mSM->addRenderQueueListener(mOverlaySystem);

  mTrayMgr = new OgreBites::TrayManager("TrayGUISystem", mWindow.render);  

  //panel = mTrayMgr->createParamsPanel(OgreBites::TL_BOTTOMRIGHT, "AvispasHUD", 200, 1);

  mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
  addInputListener(mTrayMgr);

  addInputListener(this);   
  setupScene();
}

void IG2App::setupScene(void)
{
  // create the camera
  Camera* cam = mSM->createCamera("Cam");
  cam->setNearClipDistance(1); 
  cam->setFarClipDistance(10000);
  cam->setAutoAspectRatio(true);
  //cam->setPolygonMode(Ogre::PM_WIREFRAME); 

  mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
  mCamNode->attachObject(cam);

  mCamNode->setPosition(0, 0, 1000);
  mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
  //mCamNode->setDirection(Ogre::Vector3(0, 0, -1));  
  
  // and tell it to render into the main window
  Viewport* vp = getRenderWindow()->addViewport(cam);
  vp->setBackgroundColour(Ogre::ColourValue(0.6, 0.7, 0.8));

  //------------------------------------------------------------------------

  // without light we would just get a black screen 

  Light* luz = mSM->createLight("Luz");
  luz->setType(Ogre::Light::LT_DIRECTIONAL);
  luz->setDiffuseColour(1, 1, 1);

  mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
  //mLightNode = mCamNode->createChildSceneNode("nLuz");
  mLightNode->attachObject(luz);

  mLightNode->setDirection(Ogre::Vector3(0, -1, -1));  //vec3.normalise();
  //mLightNode->setPosition(1000, 0, 2000);
 

	SceneNode* nodoBomba = mSM->getRootSceneNode()->createChildSceneNode("Bomba");
	mSM->getSceneNode("Bomba")->setPosition({ 0,0,0 });
	bomba = new Bomba(nodoBomba);
	mSM->getSceneNode("Bomba")->setScale({ 100,100,100 });
	addInputListener(bomba);
	EntidadIG::addListener(bomba);
	 
	SceneNode* nodoPlano = mSM->getRootSceneNode()->createChildSceneNode("Plano");
	plano = new Plano(nodoPlano);
	EntidadIG::addListener(plano);
	addInputListener(plano);

	Entity* platAmarilla = mSM->createEntity("mPlane1080x800");
	platAmarilla->setMaterialName("Practica1/Amarillo");
	SceneNode* nodoPlatAmarilla = mSM->getRootSceneNode()->createChildSceneNode("PlatAmarilla");
	nodoPlatAmarilla->attachObject(platAmarilla);
	nodoPlatAmarilla->setScale(0.3, 0.3, 0.3);
	nodoPlatAmarilla->setPosition(-380, 1, 282);

	SceneNode* nodoSinbad = mSM->getRootSceneNode()->createChildSceneNode("Sinbad");
	mSM->getSceneNode("Sinbad")->scale({ 10,10,10 });
	mSM->getSceneNode("Sinbad")->setPosition({ -300,50,300 });
	sinbad = new Sinbad(nodoSinbad);
	sinbad->setStatic();
	sinbad->arma();
	sinbad->setRunAnimation();
	EntidadIG::addListener(sinbad);
	addInputListener(sinbad);

	SceneNode* nodoNoria = mSM->getRootSceneNode()->createChildSceneNode("Noria");
	nodoNoria->setPosition(380, 0, -380);
	noria = new Noria(nodoNoria, 12);
	EntidadIG::addListener(noria);
	addInputListener(noria);

	SceneNode* nodoAvion = mSM->getRootSceneNode()->createChildSceneNode("Avion");
	mSM->getSceneNode("Avion")->scale({ 0.2,0.2,0.2 });
	mSM->getSceneNode("Avion")->setPosition({ -300,200,0 });
	avion = new Avion(nodoAvion);
	EntidadIG::addListener(avion);
	addInputListener(avion);


	/*SceneNode* nodoSkyPLane = mSM->getRootSceneNode()->createChildSceneNode("SkyPlane");
	Entity* skyPlane = mSM->createEntity("mPlane1080x800");
	skyPlane->setMaterialName("IG2App/space");
	nodoSkyPLane->attachObject(skyPlane);
	nodoPlatAmarilla->setPosition(0, 200, -200);*/

	mSM->setSkyPlane(true, Plane(Vector3::UNIT_Z, -2), "IG2App/SpaceSKY", 0.05, 1, true, 1, 100, 100);

 
  //------------------------------------------------------------------------
  mCamMgr = new OgreBites::CameraMan(mCamNode);
  addInputListener(mCamMgr);
  mCamMgr->setStyle(OgreBites::CS_ORBIT);  
  
  //mCamMgr->setTarget(mSinbadNode);  
  //mCamMgr->setYawPitchDist(Radian(0), Degree(30), 100);

  //------------------------------------------------------------------------

}

