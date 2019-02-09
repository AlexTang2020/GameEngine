
class AudioManager
{
public:
	// Get the one and only instance.
	static AudioManager& get()
	{
		// This function-static will be constructed on the
		// first call to this function.
		static AudioManager sSingleton;
		return sSingleton;
	}
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
};
// singleton instance
static AudioManager gAudioManager;
