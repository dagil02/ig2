#pragma once
#include "EntidadIG.h"
#include <OgreEntity.h>
#include <string>

using namespace Ogre;

class Plano : public EntidadIG
{

public:
	Plano(Ogre::SceneNode* nodo, std::string name);
	~Plano() {};

	bool keyPressed(const OgreBites::KeyboardEvent& evt) { return true; };

protected:

	Entity* plane = nullptr;
};

