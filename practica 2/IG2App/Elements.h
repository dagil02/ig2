#pragma once
#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include "IG2ApplicationContext.h"
#include "EntidadIG.h"
#include <OgreAnimation.h>
#include <OgreAnimationState.h>
#include <OgreAnimationTrack.h>
#include <OgreKeyFrame.h>
#include <OgreBillboardSet.h>

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
    void receiveEvent(messages msg) {};
};

class AspasMolino : public EntidadIG {
public:
    AspasMolino(int num_aspas, std::string name, Ogre::SceneNode* node);   //maximo numero de aspas 100
    Ogre::SceneNode* aspasNode = nullptr;
    Ogre::SceneNode* centroNode = nullptr;
    void swapCilindro();
    int numAspas;
    bool active = true;
    Aspa** aspasList;
    bool cilindro = true;
    void receiveEvent(messages msg);
};



class Molino: public EntidadIG {
public:
    Molino(int num_aspas, Ogre::SceneNode* node);   //maximo numero de aspas 100
    ~Molino();
    int numAspas;
    bool active = true;
    Ogre::SceneNode* esferaNode = nullptr;
    Ogre::Entity* techoMesh = nullptr;
    Ogre::SceneNode* cuerpoNode = nullptr;
    Ogre::SceneNode* aspasNode = nullptr;
    AspasMolino* aspas = nullptr;
    bool keyPressed(const OgreBites::KeyboardEvent& evt);  // InputListener
    virtual void frameRendered(const Ogre::FrameEvent& evt);
    void receiveEvent(messages msg);
};

class Reloj : public EntidadIG {
public:
    Reloj(Ogre::SceneNode* node);
    ~Reloj();
    Ogre::SceneNode* agujasNode = nullptr;
    bool keyPressed(const OgreBites::KeyboardEvent& evt);
    virtual void frameRendered(const Ogre::FrameEvent& evt) { }
    void receiveEvent(messages msg) {};
private:
    float rot;
};

class Tierra : public EntidadIG {
public:
    Tierra(Ogre::SceneNode* node);
    ~Tierra();
    bool keyPressed(const OgreBites::KeyboardEvent& evt);
    virtual void frameRendered(const Ogre::FrameEvent& evt) { }
    void receiveEvent(messages msg) {};
};

class Sol : public EntidadIG {
public:
    Sol(Ogre::SceneNode* node);
    ~Sol();
    bool keyPressed(const OgreBites::KeyboardEvent& evt) { return true; };
    virtual void frameRendered(const Ogre::FrameEvent& evt) { }
    void receiveEvent(messages msg) {};
};

class Avion : public EntidadIG {
public:
    Avion(Ogre::SceneNode* node);
    ~Avion();
    bool keyPressed(const OgreBites::KeyboardEvent& evt);
    virtual void frameRendered(const Ogre::FrameEvent& evt);
    void receiveEvent(messages msg);
protected:
    float rot;
    Ogre::SceneNode* focoNode = nullptr;
    Light* foco;
    bool active = true;

    //Particles
    Ogre::BillboardSet* bbSet = nullptr;
    Ogre::SceneNode* explosionNode = nullptr;
    ParticleSystem* explosionSys = nullptr;
};

class Boya : public EntidadIG {
public:
    Boya(Ogre::SceneNode* node);
    ~Boya() {};
    bool keyPressed(const OgreBites::KeyboardEvent& evt) { return true; };
    virtual void frameRendered(const Ogre::FrameEvent& evt);
    void receiveEvent(messages msg);
private:
    float duracion = 8;
    float longDesplazamiento = 40;
    AnimationState* animationState = nullptr;
    bool explota = false;
    Ogre::Entity* boya = nullptr;
};
