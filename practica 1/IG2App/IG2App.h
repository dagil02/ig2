#ifndef __IG2App_H__
#define __IG2App_H__

#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>


class Aspa {
public:
    Aspa(Ogre::SceneManager* &mSM, std::string id, Ogre::SceneNode* &aspasNode);
    ~Aspa() {};
    Ogre::SceneNode* aspaNode = nullptr;
    Ogre::SceneNode* tableroNode = nullptr;
    Ogre::SceneNode* cilindroNode = nullptr;
};

class AspasMolino {
public:
    AspasMolino(int num_aspas, Ogre::SceneManager*& mSM);   //maximo numero de aspas 100
    Ogre::SceneNode* aspasNode = nullptr;
    int numAspas;
    Aspa** aspasList;
};

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
  Ogre::SceneNode* aspas = nullptr;
  Ogre::SceneNode * aspaNode = nullptr;
  Ogre::SceneNode* tableroNode = nullptr;
  Ogre::SceneNode* cilindroNode = nullptr;
  OgreBites::CameraMan* mCamMgr = nullptr;

  //Apartado 5
  AspasMolino* molinoAspas = nullptr;

  //numero aspas
  int num = 12; //maximo de 100
 
};

#endif
