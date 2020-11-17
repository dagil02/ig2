#include "Sinbad.h"

Sinbad::Sinbad(Ogre::SceneNode* node) : EntidadIG(node)
{
	mSM = node->getCreator();

	cuerpo = mNode->createChildSceneNode();
	cuerpoMesh = mSM->createEntity("Sinbad.mesh");
	cuerpo->attachObject(cuerpoMesh);
	mNode->setScale(15, 15, 15);
	
}


bool Sinbad::keyPressed(const OgreBites::KeyboardEvent & evt)
{
	return true;
}


