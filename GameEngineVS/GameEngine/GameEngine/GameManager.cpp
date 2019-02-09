
class GameManager
{
public:
	GameManager()
	{
		// do nothing
	}
	~GameManager()
	{
		// do nothing
	}

	void run() {

	}
};
class RenderManager
{
public:
	RenderManager()
	{
		// do nothing
	}
	~RenderManager()
	{
		// do nothing
	}
	void startUp()
	{
		// start up the manager...
	}
	void shutDown()
	{
		// shut down the manager...
	}
};

class PhysicsManager { 
public:
	PhysicsManager()
	{
		// do nothing
	}
	~PhysicsManager()
	{
		// do nothing
	}
	void startUp()
	{
		// start up the manager...
	}
	void shutDown()
	{
		// shut down the manager...
	}
};
class AnimationManager { 
public:
	AnimationManager()
	{
		// do nothing
	}
	~AnimationManager()
	{
		// do nothing
	}
	void startUp()
	{
		// start up the manager...
	}
	void shutDown()
	{
		// shut down the manager...
	}
};
class TextureManager {
public:
	TextureManager()
	{
		// do nothing
	}
	~TextureManager()
	{
		// do nothing
	}
	void startUp()
	{
		// start up the manager...
	}
	void shutDown()
	{
		// shut down the manager...
	}
};
class VideoManager {
public:
	VideoManager()
	{
		// do nothing
	}
	~VideoManager()
	{
		// do nothing
	}
	void startUp()
	{
		// start up the manager...
	}
	void shutDown()
	{
		// shut down the manager...
	}
};
class MemoryManager {
public:
	MemoryManager()
	{
		// do nothing
	}
	~MemoryManager()
	{
		// do nothing
	}
	void startUp()
	{
		// start up the manager...
	}
	void shutDown()
	{
		// shut down the manager...
	}
};
class FileSystemManager {
public:
	FileSystemManager()
	{
		// do nothing
	}
	FileSystemManager()
	{
		// do nothing
	}
	void startUp()
	{
		// start up the manager...
	}
	void shutDown()
	{
		// shut down the manager...
	}
};

GameManager gameManager;
RenderManager gRenderManager;
PhysicsManager gPhysicsManager;
AnimationManager gAnimationManager;
TextureManager gTextureManager;
VideoManager gVideoManager;
MemoryManager gMemoryManager;
FileSystemManager gFileSystemManager;


int main(int argc, const char* argv)
{
	// Start up engine systems in the correct order.
	gMemoryManager.startUp();
	gFileSystemManager.startUp();
	gVideoManager.startUp();
	gTextureManager.startUp();
	gRenderManager.startUp();
	gAnimationManager.startUp();
	gPhysicsManager.startUp();
	// ...
	// Run the game.
	gameManager.run();
	// Shut everything down, in reverse order.
	// ...
	gPhysicsManager.shutDown();
	gAnimationManager.shutDown();
	gRenderManager.shutDown();
	gFileSystemManager.shutDown();
	gMemoryManager.shutDown();
	return 0;
}