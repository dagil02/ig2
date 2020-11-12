#include "Sinbad.h"

Sinbad::Sinbad(Ogre::SceneNode* node) : EntidadIG(node)
{
	mSM = node->getCreator();

	cuerpo = mNode->createChildSceneNode();
	cuerpoMesh = mSM->createEntity("Sinbad.mesh");
	cuerpo->attachObject(cuerpoMesh);
	cuerpo->setPosition(0, 1, 0);
	mNode->setScale(20, 20, 20);
	
}


bool Sinbad::keyPressed(const OgreBites::KeyboardEvent & evt)
{
	return true;
}


