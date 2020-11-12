#pragma once
#include <OgreInput.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include "EntidadIG.h"

class Sinbad : public EntidadIG
{

protected:

	Ogre::Entity* cuerpoMesh;
	Ogre::SceneNode* cuerpo;
	

public:

	Sinbad(Ogre::SceneNode* node);
	~Sinbad() { delete cuerpo; delete cuerpoMesh; };

	void frameRendered(const Ogre::FrameEvent& evt) {};

	bool keyPressed(const OgreBites::KeyboardEvent& evt);
};

