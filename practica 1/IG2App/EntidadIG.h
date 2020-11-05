#pragma once
#include <OgreInput.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreFrameListener.h>
#include <OgreMeshManager.h>
#include <SDL_keycode.h>

using namespace Ogre;


class EntidadIG : public  OgreBites::InputListener
{
public:
	//Constructora y destructora
	EntidadIG(Ogre::SceneNode* node);
	~EntidadIG();
	//Vector estático de listeners
	static std::vector<EntidadIG*> appListeners;

	static void addListener(EntidadIG* entidad) {
		appListeners.push_back(entidad);
	};
	SceneNode* getNode() { return mNode; }

protected:

	Ogre::SceneNode* mNode;
	Ogre::SceneManager* mSM;

	virtual void frameRendered(const Ogre::FrameEvent& evt);

	virtual bool keyPressed(const OgreBites::KeyboardEvent & evt)
	{
		return false;
	};

};

