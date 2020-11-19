#include "Plano.h"

Plano::Plano(Ogre::SceneNode* nodo, std::string name = "mPlane1080x800") : EntidadIG(nodo)
{
	MeshManager::getSingleton().createPlane(name,
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Plane(Vector3::UNIT_Y, 0),
		1080, 800, 100, 80, true, 1, 1.0, 1.0, Vector3::UNIT_Z);
	plane = mSM->createEntity(name);
	mNode->attachObject(plane);
	addListener(this);
}

void Plano::setMaterial(std::string name)
{
	plane->setMaterialName(name);
}

void Plano::receiveEvent(messages msg)
{
	if (msg == STOP && this->getNode()->getName() == "plano") {
		active = !active;
		if (active)plane->setMaterialName("plano");
		else plane->setMaterialName("plano_stop");
	}
}
