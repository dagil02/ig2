#include "IG2App.h"

#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include <iostream>

#define PI 3.1415926536

using namespace Ogre;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_ESCAPE)
    {
	 getRoot()->queueEndRendering();
	}
	else if (evt.keysym.sym == SDLK_r) {
		EntidadIG::sendEvent(EntidadIG::STOP);
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
  mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
  addInputListener(mTrayMgr);

  addInputListener(this);
  mSM->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
  setupScene();
}

void IG2App::setupScene(void)
{
  // create the camera
  Camera* cam = mSM->createCamera("Cam");
  cam->setNearClipDistance(1); 
  cam->setFarClipDistance(10000);
  cam->setAutoAspectRatio(true);

  mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
  mCamNode->attachObject(cam);

  mCamNode->setPosition(0, 0, 1000);
  mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);  
  
  // and tell it to render into the main window
  Viewport* vp = getRenderWindow()->addViewport(cam);
  vp->setBackgroundColour(Ogre::ColourValue(0.0, 0.0, 0.0));

  //------------------------------------------------------------------------

  // without light we would just get a black screen 

  Light* luz = mSM->createLight("Luz");
  luz->setType(Ogre::Light::LT_DIRECTIONAL);
  luz->setDiffuseColour(0.75, 0.75, 0.75);
  luz->setCastShadows(false);
  mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
  mLightNode->attachObject(luz);

  mLightNode->setDirection(Ogre::Vector3(0, -0.5, -0.5));  
 
  //------------------------------------------------------------------------

  // finally something to render

  //Skyplane
  mSM->setSkyPlane(true, Plane(Vector3::UNIT_Z, -200),
      "space", 3, 1, true, 1.0, 100, 100);

  //skyplane plano
  //mSM->setSkyPlane(true, Plane(Vector3::UNIT_Z, -200),
     // "space", 3, 1, true, 0.0, 100, 100);

  //Plano de la escena
  Ogre::SceneNode* planoNode = mSM->getRootSceneNode()->createChildSceneNode("plano");
  Plano* plano = new Plano(planoNode, "Suelo");
  plano->setMaterial("plano");
  plano->setReflejo(cam);

  //Molino
  num = 12; //numero aspas molino
  Ogre::SceneNode* molinoNode = mSM->getRootSceneNode()->createChildSceneNode("molino");
  Molino* molino = new Molino(num, molinoNode);
  molinoNode->translate(400, 100, -250);
  molinoNode->setScale(0.2, 0.2, 0.2);
  addInputListener(molino);
  EntidadIG::addListener(molino);

  //Plano molino
  Ogre::SceneNode* plano2Node = mSM->getRootSceneNode()->createChildSceneNode("plano2");
  Plano* plano2 = new Plano(plano2Node, "planoMolino");
  plano2Node->setScale(0.25, 1, 0.25);
  plano2Node->translate(400, 1, -250);
  plano2->setMaterial("naranja");

  //Avion
  Ogre::SceneNode* avionNode = mSM->getRootSceneNode()->createChildSceneNode("avion");
  Avion* avion = new Avion(avionNode);
  avionNode->setScale(0.2, 0.2, 0.2);
  addInputListener(avion);
  EntidadIG::addListener(avion);


  //Plano Sinbad
  Ogre::SceneNode* plano3Node = mSM->getRootSceneNode()->createChildSceneNode("plano3");
  Plano* plano3 = new Plano(plano3Node, "planoSinbad");
  plano3Node->setScale(0.25, 1, 0.25);
  plano3Node->translate(-400, 1, 250);
  plano3->setMaterial("rojo");

  //Sinbad
  Ogre::SceneNode* sinbadNode = mSM->getRootSceneNode()->createChildSceneNode("sinbad");
  Sinbad* sinbad = new Sinbad(sinbadNode);
  addInputListener(sinbad);
  EntidadIG::addListener(sinbad);

  //Cabeza
  cabeza = mSM->getRootSceneNode()->createChildSceneNode("cabeza");
  Ogre::Entity* ent = mSM->createEntity("sphere.mesh");
  ent->setMaterialName("cabeza");
  cabeza->attachObject(ent);
  cabeza->setScale(0.2, 0.2, 0.2);
  cabeza->translate(480,20,-200);


  //Boya
  Ogre::SceneNode* boyaNode = mSM->getRootSceneNode()->createChildSceneNode("boya");
  Boya* boya = new Boya(boyaNode);
  addInputListener(boya);
  EntidadIG::addListener(boya);
  boyaNode->setVisible(false);
  //------------------------------------------------------------------------

  mCamMgr = new OgreBites::CameraMan(mCamNode);
  addInputListener(mCamMgr);
  mCamMgr->setStyle(OgreBites::CS_ORBIT);  
  
  //------------------------------------------------------------------------

}



