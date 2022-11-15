#include "Plano.h"

Plano::Plano(SceneNode* node)
{
	mNode = node;
	mSM = mNode->getCreator();

	MeshManager::getSingleton().createPlane("mPlane1080x800", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Plane(Vector3::UNIT_Y, 0), 1080, 800, 100, 80, true, 1, 1.0, 1.0, Vector3::UNIT_Z);
	entPlane = mSM->createEntity("mPlane1080x800");
	entPlane->setMaterialName("Practica1/Agua");

	mNode->attachObject(entPlane);
	myTimer = new Ogre::Timer();
}

Plano::~Plano()
{
}

void Plano::receiveEvent(MessageType msgType, EntidadIG* entidad)
{
	/*active = !active;
	if (active) {
		entPlane->setMaterialName("Practica1/AguaEstancada");
	}
	else{
		entPlane->setMaterialName("Practica1/Agua");
	}*/
	if (msgType == STOP) {
		messageReceived = true;
		time = myTimer->getMilliseconds();
	}
	
}

void Plano::frameRendered(const Ogre::FrameEvent& evt)
{
	if (messageReceived) {
		if (time + 5000 < myTimer->getMilliseconds()) {
			entPlane->setMaterialName("Practica1/Cilindro");
			messageReceived = false;
		}
	}
	
}
