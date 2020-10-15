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
      //Apartado 3
      /*aspas->roll(Ogre::Degree(1));
      for (int i = 0; i < num; i++) {
          std::string name = "adorno_" + std::to_string(i);
          mSM->getSceneNode(name)->roll(Ogre::Degree(-1));
      }*/

      //Apartado 6
      molinoAspas->aspasNode->roll(Ogre::Degree(1));
      for (int i = 0; i < num; i++) {
          molinoAspas->aspasNode->getChild("aspa_" + std::to_string(i))->getChild("adorno" + std::to_string(i))->roll(Ogre::Degree(-1));    //Nodo Molino -> Nodo Aspa -> Nodo cilindro(adorno)
      }
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

  mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
  mCamNode->attachObject(cam);

  mCamNode->setPosition(0, 0, 1000);
  mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);  
  
  // and tell it to render into the main window
  Viewport* vp = getRenderWindow()->addViewport(cam);
  vp->setBackgroundColour(Ogre::ColourValue(0.7, 0.8, 0.9));

  //------------------------------------------------------------------------

  // without light we would just get a black screen 

  Light* luz = mSM->createLight("Luz");
  luz->setType(Ogre::Light::LT_DIRECTIONAL);
  luz->setDiffuseColour(0.75, 0.75, 0.75);

  mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
  mLightNode->attachObject(luz);

  mLightNode->setDirection(Ogre::Vector3(0, 0, -1));  
 
  //------------------------------------------------------------------------

  // finally something to render


  ///////////PRACTICA 1///////////

  //Apartado 1

  /*aspaNode = mSM->getRootSceneNode()->createChildSceneNode("aspa");

  Ogre::Entity* tab = mSM->createEntity("cube.mesh");
  tableroNode = aspaNode->createChildSceneNode("tablero");
  tableroNode->attachObject(tab);
  tableroNode->setPosition(0, 0, -300);
  tableroNode->setScale(0.7, 4, 0.1);

  Ogre::Entity* cil = mSM->createEntity("Barrel.mesh");
  cilindroNode = aspaNode->createChildSceneNode("adorno");
  cilindroNode->attachObject(cil);
  cilindroNode->setPosition(0, 170, -290);
  cilindroNode->setScale(4,9,4);

  aspaNode->roll(Ogre::Degree(-90));
  cilindroNode->roll(Ogre::Degree(90));*/

  
  //Apartado 2
  
  /*aspas = mSM->getRootSceneNode()->createChildSceneNode("aspas");
  SceneNode* mHourNode[100] = { 0 }; //numero maximo de aspas = 100
  for (int i = 0; i < num; i++) {

      
      Ogre::Entity* ent1 = mSM->createEntity("cube.mesh");
      Ogre::Entity* ent2 = mSM->createEntity("Barrel.mesh");

      std::string name0 = "aspa_" + std::to_string(i);
      std::string name1 = "tablero_" + std::to_string(i);
      std::string name2 = "adorno_" + std::to_string(i);

      Ogre::SceneNode* aspa = aspas->createChildSceneNode(name0);
      Ogre::SceneNode* tablero = aspa->createChildSceneNode(name1);
      Ogre::SceneNode* adorno = aspa->createChildSceneNode(name2);
      
      
      tablero->attachObject(ent1);
      adorno->attachObject(ent2);

      aspas->setPosition(0, 0, -300);

      tablero->setScale(0.7, 4, 0.1);
      adorno->setScale(4, 9, 4);
      adorno->setPosition(0, 170, 10);

      aspa->roll(Ogre::Degree(i * -360 / num));
      adorno->roll(Ogre::Degree(i * 360 / num));
      aspa->setPosition(sin(i * (2 * PI / num)) * 200, cos(i * (2 * PI / num)) * 200, 0);
      
      mHourNode[i] = aspa;

  
  }*/

  //Apartado 5
  num = 10; //numero aspas molino
  molinoAspas = new AspasMolino(num, mSM);

  //------------------------------------------------------------------------

  mCamMgr = new OgreBites::CameraMan(mCamNode);
  addInputListener(mCamMgr);
  mCamMgr->setStyle(OgreBites::CS_ORBIT);  
  

  //------------------------------------------------------------------------

}

AspasMolino::AspasMolino(int num_aspas, Ogre::SceneManager*& mSM)
{
    numAspas = num_aspas;

    //Creacion aspas
    aspasNode = mSM->getRootSceneNode()->createChildSceneNode("aspas");
    Aspa* aspasList[100] = { nullptr }; //numero maximo de aspas = 100
    for (int i = 0; i < numAspas; i++) {
        
        aspasList[0] = new Aspa(mSM, std::to_string(i), aspasNode);
        aspasList[0]->aspaNode->roll(Ogre::Degree(i * -360 / numAspas));
        aspasList[0]->cilindroNode->roll(Ogre::Degree(i * 360 / numAspas));
        aspasList[0]->aspaNode->setPosition(sin(i * (2 * PI / numAspas)) * 200, cos(i * (2 * PI / numAspas)) * 200, 0);
    }
}

Aspa::Aspa(Ogre::SceneManager* &mSM, std::string id, Ogre::SceneNode* &aspasNode)
{
    
  aspaNode = aspasNode->createChildSceneNode("aspa_" + id);

  Ogre::Entity* tab = mSM->createEntity("cube.mesh");
  tableroNode = aspaNode->createChildSceneNode("tablero" + id);
  tableroNode->attachObject(tab);

  Ogre::Entity* cil = mSM->createEntity("Barrel.mesh");
  cilindroNode = aspaNode->createChildSceneNode("adorno" + id);
  cilindroNode->attachObject(cil);

  tableroNode->setScale(0.7, 4, 0.1);
  cilindroNode->setScale(4, 9, 4);
  cilindroNode->setPosition(0, 170, 10);
  aspaNode->setPosition(0, 0, -300);

}
