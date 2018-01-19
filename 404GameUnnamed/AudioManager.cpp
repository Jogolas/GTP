#include "AudioManager.h"

void AudioManager::create()
{
	context = alcCreateContext(device, attribs);

	//	attribs[0] = ALC_MAX_AUXILIARY_SENDS;
	attribs[1] = 4;
}

void AudioManager::activateExt()
{
	if (alcIsExtensionPresent(device, "ALC_EXT_EFX") == AL_FALSE)
	{
		return;
	}
}

void AudioManager::destroy()
{
	//context = alcDestroyContext(context);
}

void AudioManager::initAudio()
{
	//this->create();

	device = alcOpenDevice(NULL);

	if (!device)
	{
		return;
	}
}

int AudioManager::createSource()
{
	return 0;
}

std::string AudioManager::loadSoundEffect(std::string fileName)
{
	//ALuint *buffers;
	//alGenBuffers(1, buffers);
	return 0;
}

void AudioManager::cleanUp()
{
	//this->destroy();
}