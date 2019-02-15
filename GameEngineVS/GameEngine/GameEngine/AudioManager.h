#pragma once

class AudioManager
{
public:
	AudioManager()
	{
		// Start up other managers we depend on, by
		// calling their get() functions first...
		//RenderManager::get();
		// Now start up the render manager.
		// ...
	}
	~AudioManager()
	{
		// Shut down the manager.
		// ...
	}

	void run();
};