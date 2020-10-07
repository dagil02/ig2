#include "IG2App.h"

#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>


#define PI 3.1415926536


using namespace Ogre;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt)
{
  if (evt.keysym.sym == SDLK_ESCAPE)
  {
    getRoot()->queueEndRendering();
  }
  else if (evt.keysym.sym == SDLK_g) {
	  clockNode->roll(Ogre::Degree(-1));
  }
  else if (evt.keysym.sym == SDLK_h) {
	  clockNode->roll(Ogre::Degree(-1));
	  agujasNode->roll(Ogre::Degree(1));
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
  vp->setBackgroundColour(Ogre::ColourValue(0.7, 0.8, 0.9));

  //------------------------------------------------------------------------

  // without light we would just get a black screen 

  Light* luz = mSM->createLight("Luz");
  luz->setType(Ogre::Light::LT_DIRECTIONAL);
  luz->setDiffuseColour(0.75, 0.75, 0.75);

  mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
  //mLightNode = mCamNode->createChildSceneNode("nLuz");
  mLightNode->attachObject(luz);

  mLightNode->setDirection(Ogre::Vector3(0, 0, -1));  //vec3.normalise();
  //lightNode->setPosition(0, 0, 1000);
 
  //------------------------------------------------------------------------

  // finally something to render



  // PARTE 1 DE LA PRACTICA 0

  Ogre::Entity* ent = mSM->createEntity("Sinbad.mesh");

  mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode("nSinbad");
  mSinbadNode->attachObject(ent);

  mSinbadNode->setPosition(0, 20, 0);
  mSinbadNode->setScale(20, 20, 20);
  //mSinbadNode->yaw(Ogre::Degree(-45));
  //mSinbadNode->showBoundingBox(true);
  //mSinbadNode->setVisible(false);



  //Añadir habitacion
  Ogre::Entity* hab1 = mSM->createEntity("RomanBathLower.mesh");
  mHabNode1 = mSM->getRootSceneNode()->createChildSceneNode("HabitacionB");
  mHabNode1->attachObject(hab1);
  mHabNode1->setScale(1, 1, 1);
  Ogre::Entity* hab2 = mSM->createEntity("RomanBathUpper.mesh");
  mHabNode2 = mSM->getRootSceneNode()->createChildSceneNode("HabitacionA");
  mHabNode2->attachObject(hab2);
  mHabNode2->setScale(1, 1, 1);



  //PARTE 2 DE LA PRACTICA 0

  clockNode = mSM->getRootSceneNode()->createChildSceneNode("clockNode");
  SceneNode* mHourNode[12] = { 0 };

  for (int i = 0; i < 12; i++) {

	  Ogre::Entity* ent = mSM->createEntity("sphere.mesh");

	  std::string name = "Hora " + std::to_string(i);

	  Ogre::SceneNode* node = clockNode->createChildSceneNode(name);
	  node->attachObject(ent);

	  node->setPosition(sin(i * (PI / 6)) * 400, cos(i * (PI / 6)) * 400, -300);
	  node->setScale(0.6, 0.6, 0.6);
	  
	  mHourNode[i] = node;
  }


  //Cambiar tamaño horas pares
  for (int i = 0; i < 12; i++) {

	  if (i % 2 == 1) continue;

	  std::string name = "Hora " + std::to_string(i);
	  SceneNode* aux = mSM->getSceneNode(name);
	  aux->setScale(0.3, 0.3, 0.3);
  }

  //Creando agujas
  agujasNode = clockNode->createChildSceneNode("Agujas");
  Ogre::Entity* hor = mSM->createEntity("cube.mesh");
  Ogre::SceneNode* horarioNode = agujasNode->createChildSceneNode("Horario");
  horarioNode->attachObject(hor);
  horarioNode->setPosition(0,90, -300);
  horarioNode->setScale(0.15,2, 0.15);

  Ogre::Entity* min = mSM->createEntity("cube.mesh");
  Ogre::SceneNode* minNode = agujasNode->createChildSceneNode("Minutero");
  minNode->attachObject(min);
  minNode->roll(Ogre::Degree(-90));
  minNode->setPosition(133, 0, -300);
  minNode->setScale(0.1, 3, 0.1);

  Ogre::Entity* seg = mSM->createEntity("cube.mesh");
  Ogre::SceneNode* segNode = agujasNode->createChildSceneNode("Segundero");
  segNode->attachObject(seg);
  segNode->roll(Ogre::Degree(120));
  segNode->setPosition(-110, -64, -300);
  segNode->setScale(0.05, 3, 0.05);

  //------------------------------------------------------------------------

  mCamMgr = new OgreBites::CameraMan(mCamNode);
  addInputListener(mCamMgr);
  mCamMgr->setStyle(OgreBites::CS_ORBIT);  
  
  //mCamMgr->setTarget(mSinbadNode);  
  //mCamMgr->setYawPitchDist(Radian(0), Degree(30), 100);

  //------------------------------------------------------------------------

}

