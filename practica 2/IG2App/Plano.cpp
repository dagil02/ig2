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

void Plano::setReflejo(Camera* cam)
{
	plane->getSubEntity(0)->getMaterial()->getTechnique(0)->getPass(0)->createTextureUnitState("BeachStones.jpg");

	camRef = mSM->createCamera("RefCam");

	camRef->setNearClipDistance(1);
	camRef->setFarClipDistance(10000);
	camRef->setAutoAspectRatio(true);

	camRefNode = cam->getParentSceneNode()->createChildSceneNode("refCam");
	camRefNode->attachObject(camRef);

	camRefNode->setPosition(0, 0, 1000);
	camRefNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);

	mpRef = new MovablePlane(Ogre::Vector3::UNIT_Y, 0);
	mNode->attachObject(mpRef);

	camRef->enableReflection(mpRef);
	camRef->enableCustomNearClipPlane(mpRef);




	TexturePtr rttRef = TextureManager::getSingleton().createManual(
		"rttReflejo", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, TEX_TYPE_2D,
		(Real)cam->getViewport()->getActualWidth(), (Real)cam->getViewport()->getActualHeight(),
		0, PF_R8G8B8, TU_RENDERTARGET);

	RenderTexture* renderTexture = rttRef->getBuffer()->getRenderTarget();
	Viewport* vpt = renderTexture->addViewport(camRef);
	vpt->setClearEveryFrame(true);
	vpt->setBackgroundColour(ColourValue::Black);

	TextureUnitState* tu = plane->getSubEntity(0)->getMaterial()->
		getTechnique(0)->getPass(0)->
		createTextureUnitState("rttReflejo");
	tu->setColourOperation(LBO_ADD);
	tu->setProjectiveTexturing(true, camRef);

}

void Plano::receiveEvent(messages msg)
{
	if (msg == STOP && this->getNode()->getName() == "plano") {
		active = !active;
		if (active)plane->setMaterialName("plano");
		else plane->setMaterialName("plano_stop");
	}
}
