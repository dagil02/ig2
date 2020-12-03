#pragma once
#include "EntidadIG.h"
#include <OgreMovablePlane.h>
#include <OgreCamera.h>
#include <OgreTextureManager.h>
#include <OgreViewport.h>
#include <OgreRenderTarget.h>
#include <OgreRenderTexture.h>
#include <OgreTexture.h>
#include <OgreHardwarePixelBuffer.h>
#include <OgreEntity.h>
#include <OgreSubEntity.h>
#include <OgrePass.h>
#include <OgreTextureUnitState.h>
#include <OgreMaterial.h>
#include <OgreTechnique.h>
#include <OgreFrustum.h>
#include <string>

using namespace Ogre;

class Plano : public EntidadIG
{

public:
	Plano(Ogre::SceneNode* nodo, std::string name);
	~Plano() {};

	bool keyPressed(const OgreBites::KeyboardEvent& evt) { return true; };
	void setMaterial(std::string name);
	void setReflejo(Camera* cam);
protected:
	void receiveEvent(messages msg);
	bool active = true;
	Entity* plane = nullptr;
	MovablePlane* mpRef = nullptr;
	Camera* camRef = nullptr;
	SceneNode* camRefNode = nullptr;
};

