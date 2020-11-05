#include "Plano.h"

Plano::Plano(Ogre::SceneNode* nodo, std::string name = "mPlane1080x800") : EntidadIG(nodo)
{
	MeshManager::getSingleton().createPlane(name,
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Plane(Vector3::UNIT_Y, 0),
		1080, 800, 100, 80, true, 1, 1.0, 1.0, Vector3::UNIT_Z);
	plane = mSM->createEntity(name);
	mNode->attachObject(plane);

}
