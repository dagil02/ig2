#pragma once
#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include "IG2ApplicationContext.h"

#define PI 3.1415926536

class Elements
{
};

class Aspa {
public:
    Aspa(Ogre::SceneManager*& mSM, std::string id, Ogre::SceneNode*& aspasNode);
    ~Aspa() {};
    Ogre::SceneNode* aspaNode = nullptr;
    Ogre::SceneNode* tableroNode = nullptr;
    Ogre::SceneNode* cilindroNode = nullptr;
};

class AspasMolino {
public:
    AspasMolino(int num_aspas, Ogre::SceneManager*& mSM, Ogre::SceneNode* padre);   //maximo numero de aspas 100
    Ogre::SceneNode* mainNode = nullptr;
    Ogre::SceneNode* aspasNode = nullptr;
    Ogre::SceneNode* centroNode = nullptr;
    void swapCilindro();
    int numAspas;
    Aspa** aspasList;
    bool cilindro = true;
};

class SceneObject {
public:
    SceneObject() {};
    ~SceneObject() {};
    virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) = 0;
};

class Molino: public SceneObject {
public:
    Molino(int num_aspas, Ogre::SceneManager*& mSM);   //maximo numero de aspas 100
    Ogre::SceneNode* mNode = nullptr;
    int numAspas;
    Ogre::SceneNode* esferaNode = nullptr;
    Ogre::SceneNode* cuerpoNode = nullptr;
    AspasMolino* aspas = nullptr;
    bool keyPressed(const OgreBites::KeyboardEvent& evt);  // InputListener
    //virtual void frameRendered(const Ogre::FrameEvent& evt) { }
};


