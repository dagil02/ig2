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
    mNode = mSM->getRootSceneNode()->createChildSceneNode("molino");
    aspas = new AspasMolino(num_aspas, mSM, mNode);
    //cilindro
    cuerpoNode = mNode->createChildSceneNode("cuerpo");
    Ogre::Entity* ent = mSM->createEntity("Barrel.mesh");
    cuerpoNode->attachObject(ent);
    cuerpoNode->setPosition(0, -220, -200);
    cuerpoNode->setScale(75, 100, 75);
    //esfera
    esferaNode = mNode->createChildSceneNode("cilindro");
    ent = mSM->createEntity("sphere.mesh");
    esferaNode->attachObject(ent);
    esferaNode->setPosition(0, 80, -200);
    esferaNode->setScale(1.8, 1.8, 1.8);
}

bool Molino::keyPressed(const OgreBites::KeyboardEvent& evt)
{
    if (evt.keysym.sym == SDLK_g) {
       
        aspas->aspasNode->roll(Ogre::Degree(1));

        for (int i = 0; i < numAspas; i++) {
            
            aspas->aspasList[i]->aspaNode->roll(Ogre::Degree(-1));
        }
    }

    return true;
}
