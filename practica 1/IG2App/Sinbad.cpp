#include "Sinbad.h"
#include <iostream>

Sinbad::Sinbad(Ogre::SceneNode* node) : EntidadIG(node)
{
	mSM = node->getCreator();

	cuerpo = mNode->createChildSceneNode();
	cuerpoMesh = mSM->createEntity("Sinbad.mesh");
	cuerpo->attachObject(cuerpoMesh);
	mNode->setScale(15, 15, 15);
	mNode->setPosition(-400, 75, 250);
	mNode->setInitialState();


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

	//Andar al centro
	Animation* animation = mSM->createAnimation("caminaAguas", duracion);
	NodeAnimationTrack* track = animation->createNodeTrack(0);
	track->setAssociatedNode(mNode);

	animationState = mSM->createAnimationState("caminaAguas");
	animationState->setLoop(true);
	animationState->setEnabled(true);

	Real durPaso = duracion / 2.0;
	Vector3  keyframePos(0, 0, 0);
		
	TransformKeyFrame* kf;  // 4 keyFrames: origen(0), abajo, arriba, origen(3)

	kf = track->createNodeKeyFrame(0);  // Keyframe0: origen


	kf = track->createNodeKeyFrame(durPaso * 1);  // Keyframe1: al centro
	keyframePos += Vector3(400, 0, -250);
	kf->setTranslate(keyframePos);

	kf = track->createNodeKeyFrame(durPaso * 2); // Keyframe2: regreso
	keyframePos += Vector3(-400, 0, 250);
	kf->setTranslate(keyframePos);

	kf = track->createNodeKeyFrame(0);  // Keyframe3:   origen

	animation->setInterpolationMode(Ogre::Animation::IM_SPLINE);
}


void Sinbad::frameRendered(const Ogre::FrameEvent& evt)
{

	if (dancing) dance->addTime(evt.timeSinceLastFrame);
	else {
		runBase->addTime(evt.timeSinceLastFrame);
		runTop->addTime(evt.timeSinceLastFrame);
		animationState->addTime(evt.timeSinceLastFrame);
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


