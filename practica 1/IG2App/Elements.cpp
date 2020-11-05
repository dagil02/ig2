#include "Elements.h"

#include <OgreInput.h>
#include <SDL_keycode.h>

AspasMolino::AspasMolino(int num_aspas, std::string name = "molinoAspas", Ogre::SceneNode* node = nullptr) : EntidadIG (node)
{
    numAspas = num_aspas;
    

    //Creacion centro apartado 9
    centroNode = mNode->createChildSceneNode(name + "centro");
    Ogre::Entity* ent = mSM->createEntity("Barrel.mesh");
    centroNode->attachObject(ent);
    centroNode->setScale(15, 10, 15);
    centroNode->pitch(Ogre::Degree(90));
   
    //Creacion aspas
    aspasNode = mNode->createChildSceneNode(name + "aspas");
    aspasList = new Aspa * [numAspas];
    for (int i = 0; i < numAspas; i++) {
        std::string aspaName = "aspa_" + name + std::to_string(i);
        Ogre::SceneNode* n = mNode->createChildSceneNode(aspaName);
        aspasList[i] = new Aspa(name + std::to_string(i), n);
        aspasList[i]->getNode()->roll(Ogre::Degree(i * -360 / numAspas));
        aspasList[i]->cilindroNode->roll(Ogre::Degree(i * 360 / numAspas));
        aspasList[i]->getNode()->setPosition(sin(i * (2 * PI / numAspas)) * 200, cos(i * (2 * PI / numAspas)) * 200, 0);
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


Aspa::Aspa(std::string id, Ogre::SceneNode*& node) : EntidadIG(node)
{

    Ogre::Entity* tab = mSM->createEntity("cube.mesh");
    tableroNode = mNode->createChildSceneNode("tablero_" + id);
    tableroNode->attachObject(tab);

    Ogre::Entity* cil = mSM->createEntity("Barrel.mesh");
    cilindroNode = mNode->createChildSceneNode("adorno_" + id);
    cilindroNode->attachObject(cil);

    tableroNode->setScale(0.7, 4, 0.1);
    cilindroNode->setScale(4, 9, 4);
    cilindroNode->setPosition(0, 170, 10);
    mNode->setPosition(0, 0, -300);

}

Molino::Molino(int num_aspas, Ogre::SceneNode* node): EntidadIG(node)
{
    numAspas = num_aspas;

    aspasNode = mNode->createChildSceneNode("aspas");
    aspas = new AspasMolino(num_aspas, "molinoAspas", aspasNode);
    aspas->getNode()->setPosition(0, 0, 200);
    //cilindro
    cuerpoNode = mNode->createChildSceneNode("cuerpoMolino");
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

Molino::~Molino()
{
    delete esferaNode; esferaNode = nullptr;
    delete cuerpoNode; cuerpoNode = nullptr;
    delete aspasNode; aspasNode = nullptr;
    delete aspas; aspas = nullptr;
}

bool Molino::keyPressed(const OgreBites::KeyboardEvent& evt)
{
    if (evt.keysym.sym == SDLK_g) {
       
        aspas->getNode()->roll(Ogre::Degree(1));

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

Reloj::Reloj(Ogre::SceneNode* node) : EntidadIG(node)
{
    Ogre::SceneNode* mHourNode[12] = { 0 };

    for (int i = 0; i < 12; i++) {

        Ogre::Entity* ent = mSM->createEntity("sphere.mesh");

        std::string name = "Hora " + std::to_string(i);

        Ogre::SceneNode* node = mNode->createChildSceneNode(name);
        node->attachObject(ent);

        node->setPosition(sin(i * (PI / 6)) * 400, cos(i * (PI / 6)) * 400, -300);
        node->setScale(0.6, 0.6, 0.6);

        mHourNode[i] = node;
    }



    //Creando agujas
    agujasNode = mNode->createChildSceneNode("Agujas");
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
    delete agujasNode;

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

Tierra::Tierra(Ogre::SceneNode* node) : EntidadIG(node)
{
    Ogre::Entity* tierra = mSM->createEntity("sphere.mesh");
    mNode->attachObject(tierra);
    mNode->setScale(0.5, 0.5, 0.5);
    mNode->setPosition(100, 0, 0);

}

bool Tierra::keyPressed(const OgreBites::KeyboardEvent& evt)
{
    if (evt.keysym.sym == SDLK_j) {
        mNode->rotate(Ogre::Vector3(0,1,0), Ogre::Degree(-1), Ogre::Node::TransformSpace::TS_WORLD);
    }
    return true;
}

Tierra::~Tierra()
{
}

Sol::Sol(Ogre::SceneNode* node) : EntidadIG(node)
{
    Ogre::Entity* sol = mSM->createEntity("sphere.mesh");
    mNode->attachObject(sol);
}

Sol::~Sol()
{
}

Avion::Avion(Ogre::SceneNode* node) : EntidadIG(node)
{
        /*Cuerpo*/
    Ogre::SceneNode* cuerpoNode = mNode->createChildSceneNode("cuerpo");
    Ogre::Entity* cuerpo = mSM->createEntity("sphere.mesh");
    mNode->attachObject(cuerpo);
    cuerpoNode->setScale(0.5, 0.5, 0.5);

        /*Frente*/
    Ogre::SceneNode* frenteNode = mNode->createChildSceneNode("frente");
    Ogre::Entity* frente = mSM->createEntity("Barrel.mesh");
    frenteNode->attachObject(frente);
    frenteNode->setScale(10, 5, 10);
    frenteNode->pitch(Ogre::Degree(90));
    frenteNode->setPosition(0, 0, 100);

        /*Piloto*/
    Ogre::SceneNode* pilotoNode = mNode->createChildSceneNode("piloto");
    Ogre::Entity* piloto = mSM->createEntity("ninja.mesh");
    pilotoNode->attachObject(piloto);
    pilotoNode->setScale(0.5, 0.5, 0.5);
    pilotoNode->yaw(Ogre::Degree(180));
    pilotoNode->setPosition(0, 40, 0);

        /*Alas*/
    Ogre::SceneNode* alaINode = mNode->createChildSceneNode("alaI");
    Ogre::Entity* alaI = mSM->createEntity("cube.mesh");
    alaINode->attachObject(alaI);
    alaINode->setScale(2, 0.1, 1);
    alaINode->setPosition(-180, 0, 0);

    Ogre::SceneNode* alaDNode = mNode->createChildSceneNode("alaD");
    Ogre::Entity* alaD = mSM->createEntity("cube.mesh");
    alaDNode->attachObject(alaD);
    alaDNode->setScale(2, 0.1, 1);
    alaDNode->setPosition(180, 0, 0);

        /*Helices*/
    Ogre::SceneNode* heliceNodeI = mNode->createChildSceneNode("heliceI");
    AspasMolino* aspasI = new AspasMolino(5,"molinoAspasI", heliceNodeI);
    heliceNodeI->setScale(0.15, 0.15, 0.15);
    heliceNodeI->setPosition(alaINode->getPosition().x, alaINode->getPosition().y, alaINode->getPosition().z + 50);

    Ogre::SceneNode* heliceNodeD = mNode->createChildSceneNode("heliceD");
    AspasMolino* aspasD = new AspasMolino(5,"molinoAspasD", heliceNodeD);
    heliceNodeD->setScale(0.15, 0.15, 0.15);
    heliceNodeD->setPosition(alaDNode->getPosition().x, alaDNode->getPosition().y, alaDNode->getPosition().z + 50);

}

Avion::~Avion()
{
}

bool Avion::keyPressed(const OgreBites::KeyboardEvent& evt)
{
    if (evt.keysym.sym == SDLK_g) {
        mNode->getChild("heliceI")->roll(Ogre::Degree(-8));
        mNode->getChild("heliceD")->roll(Ogre::Degree(-8));
    }
    return true;
}
