#include "Elements.h"

#include <OgreInput.h>
#include <SDL_keycode.h>

AspasMolino::AspasMolino(int num_aspas, Ogre::SceneManager*& mSM, Ogre::SceneNode* padre = nullptr) 
{
    numAspas = num_aspas;
    if (padre == nullptr) mainNode = mSM->getRootSceneNode()->createChildSceneNode("molinoAspas");
    else mainNode = padre->createChildSceneNode("molinoAspas");
    //Creacion centro apartado 9
    centroNode = mainNode->createChildSceneNode("centro");
    Ogre::Entity* ent = mSM->createEntity("Barrel.mesh");
    centroNode->attachObject(ent);
    centroNode->setScale(15, 10, 15);
    centroNode->pitch(Ogre::Degree(90));
   
    //Creacion aspas
    aspasNode = mainNode->createChildSceneNode("aspas");
    aspasList = new Aspa * [numAspas];
    for (int i = 0; i < numAspas; i++) {

        aspasList[i] = new Aspa(mSM, std::to_string(i), aspasNode);
        aspasList[i]->aspaNode->roll(Ogre::Degree(i * -360 / numAspas));
        aspasList[i]->cilindroNode->roll(Ogre::Degree(i * 360 / numAspas));
        aspasList[i]->aspaNode->setPosition(sin(i * (2 * PI / numAspas)) * 200, cos(i * (2 * PI / numAspas)) * 200, 0);
    }
}

void AspasMolino::swapCilindro()
{
    cilindro = !cilindro;

    if (cilindro) {
        centroNode->setPosition(0, 0, 0);
    }
    else {
        centroNode->setPosition(0, 0, -50);
    }
}


Aspa::Aspa(Ogre::SceneManager*& mSM, std::string id, Ogre::SceneNode*& aspasNode)
{

    aspaNode = aspasNode->createChildSceneNode("aspa_" + id);

    Ogre::Entity* tab = mSM->createEntity("cube.mesh");
    tableroNode = aspaNode->createChildSceneNode("tablero_" + id);
    tableroNode->attachObject(tab);

    Ogre::Entity* cil = mSM->createEntity("Barrel.mesh");
    cilindroNode = aspaNode->createChildSceneNode("adorno_" + id);
    cilindroNode->attachObject(cil);

    tableroNode->setScale(0.7, 4, 0.1);
    cilindroNode->setScale(4, 9, 4);
    cilindroNode->setPosition(0, 170, 10);
    aspaNode->setPosition(0, 0, -300);

}

Molino::Molino(int num_aspas, Ogre::SceneManager*& mSM)
{
    numAspas = num_aspas;
    mNode = mSM->getRootSceneNode()->createChildSceneNode("molino");
    aspas = new AspasMolino(num_aspas, mSM, mNode);
    aspas->mainNode->setPosition(0, 0, 200);
    //cilindro
    cuerpoNode = mNode->createChildSceneNode("cuerpo");
    Ogre::Entity* ent = mSM->createEntity("Barrel.mesh");
    cuerpoNode->attachObject(ent);
    cuerpoNode->setPosition(0, -220, 0);
    cuerpoNode->setScale(75, 100, 75);
    //esfera
    esferaNode = mNode->createChildSceneNode("cilindro");
    ent = mSM->createEntity("sphere.mesh");
    esferaNode->attachObject(ent);
    esferaNode->setPosition(0, 80, 0);
    esferaNode->setScale(1.8, 1.8, 1.8);
}

bool Molino::keyPressed(const OgreBites::KeyboardEvent& evt)
{
    if (evt.keysym.sym == SDLK_g) {
       
        aspas->aspasNode->roll(Ogre::Degree(1));

        for (int i = 0; i < numAspas; i++) {
            
            aspas->aspasList[i]->cilindroNode->roll(Ogre::Degree(-1));
        }
    }
    else if (evt.keysym.sym == SDLK_c) {
        aspas->swapCilindro();
    }
    else if (evt.keysym.sym == SDLK_h) {
        mNode->yaw(Ogre::Degree(-1));
    }

    return true;
}

Reloj::Reloj(Ogre::SceneManager* mSM)
{

    clockNode = mSM->getRootSceneNode()->createChildSceneNode("clockNode");
    Ogre::SceneNode* mHourNode[12] = { 0 };

    for (int i = 0; i < 12; i++) {

        Ogre::Entity* ent = mSM->createEntity("sphere.mesh");

        std::string name = "Hora " + std::to_string(i);

        Ogre::SceneNode* node = clockNode->createChildSceneNode(name);
        node->attachObject(ent);

        node->setPosition(sin(i * (PI / 6)) * 400, cos(i * (PI / 6)) * 400, -300);
        node->setScale(0.6, 0.6, 0.6);

        mHourNode[i] = node;
    }


    ////Cambiar tamaño horas pares
    //for (int i = 0; i < 12; i++) {

    //    if (i % 2 == 1) continue;

    //    std::string name = "Hora " + std::to_string(i);
    //    Ogre::SceneNode* aux = mSM->getSceneNode(name);
    //    aux->setScale(0.3, 0.3, 0.3);
    //}

    //Creando agujas
    agujasNode = clockNode->createChildSceneNode("Agujas");
    Ogre::Entity* hor = mSM->createEntity("cube.mesh");
    Ogre::SceneNode* horarioNode = agujasNode->createChildSceneNode("Horario");
    horarioNode->attachObject(hor);
    horarioNode->setPosition(0, 90, -300);
    horarioNode->setScale(0.15, 2, 0.15);

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
    segNode->setPosition(-sin(2*PI/3) * 140, cos(2 * PI / 3) * 140, -300);
    segNode->setScale(0.05, 3, 0.05);
    rot = 120;
}

Reloj::~Reloj() 
{
    delete clockNode;
    delete agujasNode;

    clockNode = nullptr;
    agujasNode = nullptr;

}

bool Reloj::keyPressed(const OgreBites::KeyboardEvent& evt)
{
    if (evt.keysym.sym == SDLK_h) 
    {
        
        agujasNode->getChild("Segundero")->roll(Ogre::Degree(-1));
        rot--;
        agujasNode->getChild("Segundero")->setPosition(-sin(rot/180 * PI) * 140, cos(rot / 180 * PI) * 140, -300);
    }

    return true;
}

Tierra::Tierra(Ogre::SceneManager* mSM)
{
    node = mSM->getRootSceneNode()->createChildSceneNode("Tierra");
    Ogre::Entity* tierra = mSM->createEntity("sphere.mesh");
    node->attachObject(tierra);
    node->setScale(0.5, 0.5, 0.5);
    node->setPosition(100, 0, 0);
}

bool Tierra::keyPressed(const OgreBites::KeyboardEvent& evt)
{
    if (evt.keysym.sym == SDLK_j) {
        node->rotate(Ogre::Vector3(0,1,0), Ogre::Degree(-1), Ogre::Node::TransformSpace::TS_WORLD);
    }
    return true;
}

Tierra::~Tierra()
{
    delete node;
    node = nullptr;
}

Sol::Sol(Ogre::SceneManager* mSM)
{
    node = mSM->getRootSceneNode()->createChildSceneNode("Sol");
    Ogre::Entity* sol = mSM->createEntity("sphere.mesh");
    node->attachObject(sol);
}

Sol::~Sol()
{
    delete node;
    node = nullptr;
}