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
  else if (evt.keysym.sym == SDLK_g) {
	mSM->getSceneNode("Clock")->roll(Ogre::Degree(1));
  }
  else if (evt.keysym.sym == SDLK_h) {
	  tierraFake->pitch(Ogre::Degree(5));
	  Ogre::AxisAlignedBox aabbAvion = mSM->getSceneNode("Avion")->_getWorldAABB();


	/*  for (std::vector<SceneNode*>::iterator it = dronVector.begin(); it != dronVector.end(); it++) {
		  SceneNode* s = *it;
		  if (!s->_getWorldAABB().intersection(aabbAvion).isNull()) {
			  mSM->destroySceneNode(s->getName());
			  dronVector.erase(it);
		  }
	  }*/
	  for (int i = 0; i < dronVector.size(); i++) {
		  if (!dronVector.at(i)->_getWorldAABB().intersection(aabbAvion).isNull()) {
			  mSM->destroySceneNode(dronVector.at(i));
			  dronVector.erase(dronVector.begin() + i);
		  }
	  }
	  panel->setParamValue("Avispas", std::to_string(dronVector.size()));

	  //for (SceneNode* n : dronVector)
	  //{
		 //if (!n->_getWorldAABB().intersection(aabbAvion).isNull()) {
			// n->flipVisibility();
		 //}
	  //}
	  if (dronVector.size() == 0) {
		  dron->changeColor();
	  }
  }
  else if (evt.keysym.sym == SDLK_j) {
	  tierraFake->yaw(Ogre::Degree(5));
  }
  else if (evt.keysym.sym == SDLK_q) {
	  //noria->frameRendered();
  }
  else if (evt.keysym.sym == SDLK_p) {
	  mSM->getSceneNode("Plano")->yaw(Degree(1));
  }
  else if (evt.keysym.sym == SDLK_r) {
	  //plano->sendEvent(DEFAULT, plano);
	  removeInputListener(avion);
	  avion->explode();
	  avion->sendEvent(PLANE_EXPLOTION, avion);
  }
  else if (evt.keysym.sym == SDLK_1) {
	  //Poner dos armas
	  sinbad->arma();
  }
  else if (evt.keysym.sym == SDLK_2) {
	  //Poner un arma en la derecha
	  sinbad->arma(true);
  }
  else if (evt.keysym.sym == SDLK_3) {
	  //Quitar toda arma
	  sinbad->arma(false);
  }
  else if (evt.keysym.sym == SDLK_4) {
	  //Cambiar de mano la espada
	  sinbad->cambiaEspada();
  }
  else if (evt.keysym.sym == SDLK_c) {
	  sinbad->danceOrGo();
  }
  else if (evt.keysym.sym == SDLK_t) {
	  plano->sendEvent(STOP, plano);
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
  delete aspa; aspa = nullptr;
  delete noria; noria = nullptr;
  delete muñeco; muñeco = nullptr;
  delete plano; plano = nullptr;
  delete avion; avion = nullptr;
  delete dron; dron = nullptr;

  std::vector<SceneNode*> dronVector;

  SceneNode* tierraFake;
  for (int i = 0; i < dronVector.size(); i++) {
		delete dronVector.at(i);
		//dronVector.erase(dronVector.begin() + i);
  }
  dronVector.clear();
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
  luz->setDiffuseColour(0.75, 0.75, 0.75);

  mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
  //mLightNode = mCamNode->createChildSceneNode("nLuz");
  mLightNode->attachObject(luz);

  mLightNode->setDirection(Ogre::Vector3(0, -1, -1));  //vec3.normalise();
  //mLightNode->setPosition(1000, 0, 2000);
 
  //------------------------------------------------------------------------

  // finally something to render

  //Ogre::Entity* ent = mSM->createEntity("Sinbad.mesh");

  //mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode("nSinbad");
  //mSinbadNode->attachObject(ent);
 
  //
  ////mSinbadNode->setPosition(400, 100, -300);
  //mSinbadNode->setScale(20, 20, 20);
  ////mSinbadNode->yaw(Ogre::Degree(-45));
  ////mSinbadNode->showBoundingBox(true);
  ////mSinbadNode->setVisible(false);

  //------------------------------------------------------------------------
  
  // RELOJ


  //Ogre::SceneNode* clock = mSM->getRootSceneNode()->createChildSceneNode("Clock");
  //Ogre::SceneNode* hours = clock->createChildSceneNode("Hours");
  //float r = 300.0, scale = 0.4, scalePar = 0.2;
  //for (int i = 0; i < 12; i++) {
	 // Ogre::Entity* ent = mSM->createEntity("sphere.mesh");
	 // std::string name = "Hora " + std::to_string(i + 1);
	 // hours->createChildSceneNode(name)->attachObject(ent);
	 // if (i % 2 == 0)mSM->getSceneNode(name)->setScale(scalePar, scalePar, scalePar);
	 // else mSM->getSceneNode(name)->setScale(scale, scale, scale);
	 // float f = (i / 12.0 * 2 * Math::PI + Math::PI / 2);
	 // hours->getChild(name)->setPosition(Math::Cos(f)*r, Math::Sin(f)*r, 0.0);


  //}
  //Ogre::Entity* ent = mSM->createEntity("cube.mesh");
  //clock->createChildSceneNode("HourNeedle")->attachObject(ent);
  //mSM->getSceneNode("HourNeedle")->setScale(1.8, 0.1, 0.1);
  //mSM->getSceneNode("HourNeedle")->setPosition(70, 0, 0);

  //ent = mSM->createEntity("cube.mesh");
  //clock->createChildSceneNode("MinuteNeedle")->attachObject(ent);
  //mSM->getSceneNode("MinuteNeedle")->setScale(2.4, 0.1, 0.1);
  //mSM->getSceneNode("MinuteNeedle")->setPosition(0, 90, 0);
  //mSM->getSceneNode("MinuteNeedle")->roll(Ogre::Degree(90));

  //ent = mSM->createEntity("cube.mesh");
  //clock->createChildSceneNode("SecondNeedle")->attachObject(ent);
  //mSM->getSceneNode("SecondNeedle")->setScale(3, 0.05, 0.05);
  //mSM->getSceneNode("SecondNeedle")->setPosition(-80, -80, 0);
  //mSM->getSceneNode("SecondNeedle")->roll(Ogre::Degree(45));

  //------------------------------------------------------------------------
  //// PLANO
  //SceneNode* nodoPlano = mSM->getRootSceneNode()->createChildSceneNode("Plano");
  //plano = new Plano(nodoPlano);
  //EntidadIG::addListener(plano);

  //// NORIA
  //SceneNode* nodoNoria = nodoPlano->createChildSceneNode("Noria");
  //noria = new Noria(nodoNoria, 12);
  //EntidadIG::addListener(noria);
  //addInputListener(noria);

  //// MUÑECO
  //SceneNode* nodoMuñeco = nodoPlano->createChildSceneNode("Muñeco");
  //muñeco = new Muñeco(nodoMuñeco);
  //EntidadIG::addListener(muñeco);
  //addInputListener(muñeco);
  //nodoMuñeco->setScale(0.4, 0.4, 0.4);
  //nodoMuñeco->setPosition(200, 40, 200);
  //nodoMuñeco->yaw(Degree(230));

  //------------------------------------------------------------------------
  
  /*tierraFake = mSM->getRootSceneNode()
	  ->createChildSceneNode("tierra fake");

  SceneNode* nodoAvion = tierraFake->createChildSceneNode("Avion");
  mSM->getSceneNode("Avion")->scale({ 0.1,0.1,0.1 });
  mSM->getSceneNode("Avion")->setPosition({ 0,310,0 });
  avion = new Avion(nodoAvion);

  SceneNode* nodoDronNodriza = mSM->getRootSceneNode()->createChildSceneNode("DronNodriza");
  mSM->getSceneNode("DronNodriza")->scale({ 0.05,0.05,0.05 });
  mSM->getSceneNode("DronNodriza")->setPosition({ 0,0,305 });
  dron = new Dron(nodoDronNodriza,3,0,false);
  addInputListener(dron);

  Entity* ent = mSM->createEntity("sphere.mesh");
  ent->setMaterialName("Practica1/Cian");
  SceneNode* Planeta = mSM->getRootSceneNode()->createChildSceneNode("Planeta");
  Planeta->attachObject(ent);
  mSM->getSceneNode("Planeta")->scale({ 3,3,3 });

  for (int i = 0; i < 400; i++) {
	  Dron* dron;
	  std::string name = "DronAvispa" + std::to_string(i+1);
	  SceneNode* dronNode = mSM->getRootSceneNode()->createChildSceneNode(name);
	  dron = new Dron(mSM->getSceneNode(name), 3, i+1 , true);
	  addInputListener(dron);
	  dronVector.push_back(dronNode);
	  int dir = rand() % 360;
	  mSM->getSceneNode(name)->roll(Ogre::Degree(dir));
	  mSM->getSceneNode(name)->scale({0.05,0.05,0.05});
	  mSM->getSceneNode(name)->setPosition({ 0,0,305 });
  }
  panel->setAllParamNames({ "Avispas" });
  panel->setAllParamValues({ std::to_string(dronVector.size()) });*/
  //------------------------------------------------------------------------

	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
	Entity* ent = mSM->createEntity("sphere.mesh");
	ent->setMaterialName("Practica1/Cian");
	SceneNode* Planeta = mSM->getRootSceneNode()->createChildSceneNode("Planeta");
	Planeta->attachObject(ent);
	mSM->getSceneNode("Planeta")->scale({ 3,3,3 });

 
	SceneNode* nodoSinbad = mSM->getRootSceneNode()->createChildSceneNode("Sinbad");
	mSM->getSceneNode("Sinbad")->scale({ 10,10,10 });
	mSM->getSceneNode("Sinbad")->setPosition({ 0,350,0 });
	sinbad = new Sinbad(nodoSinbad);
	addInputListener(sinbad);

	//------------------------------------------------------------------------

	//SceneNode* nodoBomba = mSM->getRootSceneNode()->createChildSceneNode("Bomba");
	//mSM->getSceneNode("Bomba")->setPosition({ 0,0,0 });
	//bomba = new Bomba(nodoBomba);
	//mSM->getSceneNode("Bomba")->setScale({ 100,100,100 });
	//addInputListener(bomba);
	//EntidadIG::addListener(bomba);

	//SceneNode* nodoPlano = mSM->getRootSceneNode()->createChildSceneNode("Plano");
	//plano = new Plano(nodoPlano);
	//EntidadIG::addListener(plano);
	//addInputListener(plano);

	///*MeshManager::getSingleton().createPlane("mPlane1080x800", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	//	Plane(Vector3::UNIT_Y, 0), 1080, 800, 100, 80, true, 1, 1.0, 1.0, Vector3::UNIT_Z);*/
	//Entity* platRoja = mSM->createEntity("mPlane1080x800");
	//platRoja->setMaterialName("Practica1/Rojo");
	//SceneNode* nodoPlatRoja= mSM->getRootSceneNode()->createChildSceneNode("PlatRoja");
	//nodoPlatRoja->attachObject(platRoja);
	//nodoPlatRoja->setScale(0.3, 0.3, 0.3);
	//nodoPlatRoja->setPosition(380, 1, -282);

	//Entity* platAmarilla = mSM->createEntity("mPlane1080x800");
	//platAmarilla->setMaterialName("Practica1/Amarillo");
	//SceneNode* nodoPlatAmarilla = mSM->getRootSceneNode()->createChildSceneNode("PlatAmarilla");
	//nodoPlatAmarilla->attachObject(platAmarilla);
	//nodoPlatAmarilla->setScale(0.3, 0.3, 0.3);
	//nodoPlatAmarilla->setPosition(-380, 1, 282);

	//SceneNode* nodoSinbad = mSM->getRootSceneNode()->createChildSceneNode("Sinbad");
	//mSM->getSceneNode("Sinbad")->scale({ 10,10,10 });
	//mSM->getSceneNode("Sinbad")->setPosition({ -300,50,300 });
	//sinbad = new Sinbad(nodoSinbad);
	//sinbad->setStatic();
	//sinbad->arma();
	//sinbad->setRunAnimation();
	//EntidadIG::addListener(sinbad);
	//addInputListener(sinbad);

	//SceneNode* nodoNoria = mSM->getRootSceneNode()->createChildSceneNode("Noria");
	//nodoNoria->setPosition(380, 0, -380);
	//noria = new Noria(nodoNoria, 12);
	//EntidadIG::addListener(noria);
	//addInputListener(noria);

	//SceneNode* nodoMuñeco = mSM->getRootSceneNode()->createChildSceneNode("Muñeco");
	//nodoMuñeco->setScale(0.2, 0.2, 0.2);
	//nodoMuñeco->setPosition(500, 20, -200);
	//muñeco = new Muñeco(nodoMuñeco);
	//EntidadIG::addListener(muñeco);
	//addInputListener(muñeco);

	//SceneNode* nodoAvion = mSM->getRootSceneNode()->createChildSceneNode("Avion");
	//mSM->getSceneNode("Avion")->scale({ 0.2,0.2,0.2 });
	//mSM->getSceneNode("Avion")->setPosition({ -300,200,0 });
	//avion = new Avion(nodoAvion);
	//EntidadIG::addListener(avion);
	//addInputListener(avion);

	//BillboardSet* bbSet = mSM->createBillboardSet("Niebla", 3);
	//bbSet->setDefaultDimensions(700, 500);
	//bbSet->setMaterialName("IG2App/Niebla");
	//nodoPlano->attachObject(bbSet);
	//Billboard* bb = bbSet->createBillboard(Vector3(200, 200, 200));
	//Billboard* bb1 = bbSet->createBillboard(Vector3(100, 200, 200));
	//Billboard* bb2 = bbSet->createBillboard(Vector3(300, 200, 200));
 
  //------------------------------------------------------------------------
  mCamMgr = new OgreBites::CameraMan(mCamNode);
  addInputListener(mCamMgr);
  mCamMgr->setStyle(OgreBites::CS_ORBIT);  
  
  //mCamMgr->setTarget(mSinbadNode);  
  //mCamMgr->setYawPitchDist(Radian(0), Degree(30), 100);

  //------------------------------------------------------------------------

}

