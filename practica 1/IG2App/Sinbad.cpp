#include "Sinbad.h"
#include <iostream>

Sinbad::Sinbad(Ogre::SceneNode* node) : EntidadIG(node)
{
	mSM = node->getCreator();

	cuerpo = mNode->createChildSceneNode();
	cuerpoMesh = mSM->createEntity("Sinbad.mesh");
	cuerpo->attachObject(cuerpoMesh);
	mNode->setScale(15, 15, 15);
	


	// DANCE
	dance = cuerpoMesh->getAnimationState("Dance");
	dance->setLoop(true);
	dance->setEnabled(dancing);
	
	
	// ANDAR
	runBase = cuerpoMesh->getAnimationState("RunBase");
	runBase->setLoop(true);
	runBase->setEnabled(!dancing);

	runTop = cuerpoMesh->getAnimationState("RunTop");
	runTop->setLoop(true);
	runTop->setEnabled(!dancing);

	//Espadas
	right = mSM->createEntity("Sword.mesh");
	left = mSM->createEntity("Sword.mesh");
	left->setVisible(false);

	cuerpoMesh->attachObjectToBone("Handle.R", right);
	cuerpoMesh->attachObjectToBone("Handle.L", left);
}


void Sinbad::frameRendered(const Ogre::FrameEvent& evt)
{

	if (dancing) dance->addTime(evt.timeSinceLastFrame);
	else {
		runBase->addTime(evt.timeSinceLastFrame);
		runTop->addTime(evt.timeSinceLastFrame);
	}
}

bool Sinbad::keyPressed(const OgreBites::KeyboardEvent & evt)
{
	if (evt.keysym.sym == SDLK_c)
	{
		swapAnim();
	}else if (evt.keysym.sym == SDLK_e)
	{
		swapEspadas();
	}
	return true;
}

void Sinbad::swapAnim()
{
	dancing = !dancing;
	dance->setEnabled(dancing);
	runTop->setEnabled(!dancing);
	runBase->setEnabled(!dancing);
}

void Sinbad::swapEspadas()
{
	derecha = !derecha;
	right->setVisible(derecha);
	left->setVisible(!derecha);
}


