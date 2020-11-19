#pragma once
#include <OgreInput.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreAnimation.h>
#include <OgreSkeleton.h>
#include <OgreAnimationState.h>
#include <OgreAnimationTrack.h>
#include <OgreKeyFrame.h>
#include "EntidadIG.h"

class Sinbad : public EntidadIG
{

protected:

	Ogre::Entity* cuerpoMesh;
	Ogre::SceneNode* cuerpo;
	
	AnimationState* runBase = nullptr;
	AnimationState* runTop = nullptr;
	AnimationState* dance = nullptr;
	bool dancing = false;
	bool derecha = true;

	//Espada
	Ogre::Entity* right = nullptr;
	Ogre::Entity* left = nullptr;

	void swapAnim();
	void swapEspadas();
public:

	Sinbad(Ogre::SceneNode* node);
	~Sinbad() { delete cuerpo; delete cuerpoMesh; };

	void frameRendered(const Ogre::FrameEvent& evt);

	bool keyPressed(const OgreBites::KeyboardEvent& evt);

private:
	float duracion = 8;
	AnimationState* animationState = nullptr;
	Vector3 initPos;
};

