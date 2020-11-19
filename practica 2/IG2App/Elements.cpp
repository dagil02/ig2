#include "Elements.h"

#include <OgreInput.h>
#include <SDL_keycode.h>
#include <iostream>

AspasMolino::AspasMolino(int num_aspas, std::string name = "molinoAspas", Ogre::SceneNode* node = nullptr) : EntidadIG (node)
{
    numAspas = num_aspas;
    

    //Creacion centro apartado 9
    centroNode = mNode->createChildSceneNode(name + "centro");
    Ogre::Entity* ent = mSM->createEntity("Barrel.mesh");
    ent->setMaterialName("metal");
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

    addListener(this);
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

void AspasMolino::receiveEvent(messages msg)
{
    if (msg == STOP) {
        active = !active;
        for (int i = 0; i < numAspas; i++) {
            aspasList[i]->cilindroNode->setVisible(active);
        }
    }
}


Aspa::Aspa(std::string id, Ogre::SceneNode*& node) : EntidadIG(node)
{

    Ogre::Entity* tab = mSM->createEntity("cube.mesh");
    tab->setMaterialName("marron");
    tableroNode = mNode->createChildSceneNode("tablero_" + id);
    tableroNode->attachObject(tab);

    Ogre::Entity* cil = mSM->createEntity("Barrel.mesh");
    cilindroNode = mNode->createChildSceneNode("adorno_" + id);
    cil->setMaterialName("celeste");
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
    ent->setMaterialName("paredPiedra");
    cuerpoNode->attachObject(ent);
    cuerpoNode->setPosition(0, -220, 0);
    cuerpoNode->setScale(75, 100, 75);
    //esfera
    esferaNode = mNode->createChildSceneNode("cilindro");
    techoMesh = mSM->createEntity("sphere.mesh");
    techoMesh->setMaterialName("amarillo");
    esferaNode->attachObject(techoMesh);
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
   if (evt.keysym.sym == SDLK_c) {
        aspas->swapCilindro();
    }
    else if (evt.keysym.sym == SDLK_h) {
        mNode->yaw(Ogre::Degree(-1));
    }

    return true;
}

void Molino::frameRendered(const Ogre::FrameEvent& evt)
{
    if (active) {
        aspas->getNode()->roll(Ogre::Degree(1));

        for (int i = 0; i < numAspas; i++) {

            aspas->aspasList[i]->cilindroNode->roll(Ogre::Degree(-1));
        }
    }
}

void Molino::receiveEvent(messages msg)
{
    if (msg == STOP) {
        active = !active;
        if (active) {
            techoMesh->setMaterialName("amarillo");
        }else techoMesh->setMaterialName("rojo");
    }
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
    cuerpo->setMaterialName("rojo");
    mNode->attachObject(cuerpo);
    cuerpoNode->setScale(0.5, 0.5, 0.5);

        /*Frente*/
    Ogre::SceneNode* frenteNode = mNode->createChildSceneNode("frente");
    Ogre::Entity* frente = mSM->createEntity("Barrel.mesh");
    frente->setMaterialName("naranja");
    frenteNode->attachObject(frente);
    frenteNode->setScale(10, 5, 10);
    frenteNode->pitch(Ogre::Degree(90));
    frenteNode->setPosition(0, 0, 100);

        /*Piloto*/
    Ogre::SceneNode* pilotoNode = mNode->createChildSceneNode("piloto");
    Ogre::Entity* piloto = mSM->createEntity("ninja.mesh");
    piloto->setMaterialName("amarillo");
    pilotoNode->attachObject(piloto);
    pilotoNode->setScale(0.5, 0.5, 0.5);
    pilotoNode->yaw(Ogre::Degree(180));
    pilotoNode->setPosition(0, 40, 0);

        /*Alas*/
    Ogre::SceneNode* alaINode = mNode->createChildSceneNode("alaI");
    Ogre::Entity* alaI = mSM->createEntity("cube.mesh");
    alaI->setMaterialName("tiles");
    alaINode->attachObject(alaI);
    alaINode->setScale(2, 0.1, 1);
    alaINode->setPosition(-180, 0, 0);

    Ogre::SceneNode* alaDNode = mNode->createChildSceneNode("alaD");
    Ogre::Entity* alaD = mSM->createEntity("cube.mesh");
    alaD->setMaterialName("tiles");
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

    //rotacion inicial y posicion
    rot = 0;
    mNode->setPosition(-sin(rot / 180 * PI) * 200, mNode->getPosition().y, cos(rot / 180 * PI) * 200);
    mNode->yaw(Ogre::Degree(-90));

    //Foco

    foco = mSM->createLight("FocoAvion");
    foco->setType(Ogre::Light::LT_SPOTLIGHT);
    foco->setDiffuseColour(0.75, 0.75, 0.75);
    foco->setSpotlightInnerAngle(Ogre::Degree(5.0f));
    foco->setSpotlightOuterAngle(Ogre::Degree(70.0f));
    foco->setDirection(Ogre::Vector3(1, -1, 0));

    focoNode = mNode->createChildSceneNode("nfoco");
    focoNode->attachObject(foco);

    //Cartel
    bbSet = mSM->createBillboardSet("Cartel", 1);
    bbSet->setDefaultDimensions(200, 150);
    bbSet->setMaterialName("cartel");
    
    Billboard* bb = bbSet->createBillboard(Vector3(0, 0, 0));
    
    Ogre::SceneNode* cartelNode = mNode->createChildSceneNode("cartelNode");
    
    cartelNode->translate(0, 0, -300);
    cartelNode->attachObject(bbSet);

    
}

Avion::~Avion()
{
}

bool Avion::keyPressed(const OgreBites::KeyboardEvent& evt)
{
    return true;
}

void Avion::frameRendered(const Ogre::FrameEvent& evt)
{

    //Helices
    mNode->getChild("heliceI")->roll(Ogre::Degree(-8));
    mNode->getChild("heliceD")->roll(Ogre::Degree(-8));
    

    if (active) {
        //Movimiento
        mNode->setPosition(-sin(rot / 180 * PI) * 200, 150, cos(rot / 180 * PI) * 200);
        mNode->yaw(Ogre::Degree(-1));
        rot++;
    }
}

void Avion::receiveEvent(messages msg)
{
    foco->setVisible(active);

    if (msg == STOP) {
        active = !active;
        foco->setVisible(active);
        mNode->setVisible(active);
    }
}

Boya::Boya(Ogre::SceneNode* node) : EntidadIG(node)
{
    Ogre::Entity* boya = mSM->createEntity("Barrel.mesh");
    boya->setMaterialName("tiles");
    mNode->attachObject(boya);
    mNode->setScale(15, 15, 15);
    mNode->setInitialState();

    Animation* animation = mSM->createAnimation("animVV", duracion); 
    NodeAnimationTrack* track = animation->createNodeTrack(0); 
    track->setAssociatedNode(mNode); 
    
    animationState = mSM->createAnimationState("animVV");
    animationState->setLoop(true);
    animationState->setEnabled(true);

    Real durPaso = duracion / 4.0;
    Vector3  keyframePos(0.0);
    Vector3 src(0, 0, 1);

    TransformKeyFrame* kf;  // 4 keyFrames: origen(0), abajo, arriba, origen(3)

    kf = track-> createNodeKeyFrame(durPaso* 0);  // Keyframe0: origen

    kf = track-> createNodeKeyFrame(durPaso* 1);   // Keyframe1: abajo
    keyframePos+=Ogre::Vector3::NEGATIVE_UNIT_Y * longDesplazamiento;
    kf-> setTranslate(keyframePos); // Abajo  
    kf-> setRotation(src.getRotationTo(Vector3(1, 0, 1))); // Yaw(45) 

    kf = track-> createNodeKeyFrame(durPaso* 3); // Keyframe2: arriba
    keyframePos+=Ogre::Vector3::UNIT_Y * longDesplazamiento * 2;
    kf-> setTranslate(keyframePos);  // Arriba
    kf-> setRotation(src.getRotationTo(Vector3(-1, 0, 1)));  // Yaw(-45)

    kf = track-> createNodeKeyFrame(durPaso* 4);  // Keyframe3:   origen


    animation->setInterpolationMode(Ogre::Animation::IM_SPLINE);
}

void Boya::frameRendered(const Ogre::FrameEvent& evt)
{
    animationState->addTime(evt.timeSinceLastFrame);
}
