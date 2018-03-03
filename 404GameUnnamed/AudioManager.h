//#include "al.h"
//#include "alc.h"
//#include "windows.h"
//#include <cstdlib>
//#include <iostream>
//#include <string> 
//
//class AudioManager
//{
//
//public:
//	AudioManager();
//	~AudioManager();
//	void create();
//	void activateExt();
//	void destroy();
//	void alGenBuffers(ALsizei n, ALuint *buffers);
//	void alDeleteBuffers(ALsizei n, ALuint *buffers);
//	void initAudio();
//	int createSource();
//	std::string loadSoundEffect(std::string fileName);
//	void cleanUp();
//
//private:
//	ALCcontext *context = NULL;
//	ALCdevice *device = NULL;
//	ALint attribs[4] = { 0 };
//	ALCint iSends = 0;
//};
//
//AudioManager::AudioManager()
//{
//
//}
//
//AudioManager::~AudioManager()
//{
//
//}