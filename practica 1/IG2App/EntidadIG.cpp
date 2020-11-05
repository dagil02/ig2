#include "EntidadIG.h"


std::vector<EntidadIG*> EntidadIG::appListeners = std::vector<EntidadIG*>(0, nullptr);

EntidadIG::EntidadIG(Ogre::SceneNode* node) : mNode(node)
{	mSM = mNode->getCreator();
}

EntidadIG::~EntidadIG()
{
	for (auto i : appListeners) delete i;
	appListeners.clear();
	delete mNode;
}

void EntidadIG::frameRendered(const Ogre::FrameEvent& evt)
{
	Ogre::Real time = evt.timeSinceLastFrame;
}
