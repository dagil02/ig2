#pragma once
#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include "IG2ApplicationContext.h"
#include "EntidadIG.h"

#define PI 3.1415926536

class Elements
{
};

class Aspa : public EntidadIG {
public:
    Aspa(std::string id, Ogre::SceneNode*& node);
    ~Aspa() {};
    Ogre::SceneNode* aspaNode = nullptr;
    Ogre::SceneNode* tableroNode = nullptr;
    Ogre::SceneNode* cilindroNode = nullptr;
};

class AspasMolino : public EntidadIG {
public:
    AspasMolino(int num_aspas, std::string name, Ogre::SceneNode* node);   //maximo numero de aspas 100
    Ogre::SceneNode* aspasNode = nullptr;
    Ogre::SceneNode* centroNode = nullptr;
    void swapCilindro();
    int numAspas;
    Aspa** aspasList;
    bool cilindro = true;
};



class Molino: public EntidadIG {
public:
    Molino(int num_aspas, Ogre::SceneNode* node);   //maximo numero de aspas 100
    ~Molino();
    int numAspas;
    Ogre::SceneNode* esferaNode = nullptr;
    Ogre::SceneNode* cuerpoNode = nullptr;
    Ogre::SceneNode* aspasNode = nullptr;
    AspasMolino* aspas = nullptr;
    bool keyPressed(const OgreBites::KeyboardEvent& evt);  // InputListener
    virtual void frameRendered(const Ogre::FrameEvent& evt);
};

class Reloj : public EntidadIG {
public:
    Reloj(Ogre::SceneNode* node);
    ~Reloj();
    Ogre::SceneNode* agujasNode = nullptr;
    bool keyPressed(const OgreBites::KeyboardEvent& evt);
    virtual void frameRendered(const Ogre::FrameEvent& evt) { }

private:
    float rot;
};

class Tierra : public EntidadIG {
public:
    Tierra(Ogre::SceneNode* node);
    ~Tierra();
    bool keyPressed(const OgreBites::KeyboardEvent& evt);
    virtual void frameRendered(const Ogre::FrameEvent& evt) { }
};

class Sol : public EntidadIG {
public:
    Sol(Ogre::SceneNode* node);
    ~Sol();
    bool keyPressed(const OgreBites::KeyboardEvent& evt) { return true; };
    virtual void frameRendered(const Ogre::FrameEvent& evt) { }
};

class Avion : public EntidadIG {
public:
    Avion(Ogre::SceneNode* node);
    ~Avion();
    bool keyPressed(const OgreBites::KeyboardEvent& evt);
    virtual void frameRendered(const Ogre::FrameEvent& evt);

protected:
    float rot;
    Ogre::SceneNode* focoNode = nullptr;
    Light* foco;
};
