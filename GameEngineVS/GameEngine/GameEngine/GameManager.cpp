#include "Header.h"

class GameManager
{
public:
	RenderManager rendManager;

	GameManager()
	{
		// do nothing
	}
	~GameManager()
	{
		// do nothing
	}

	void run() {	
		rendManager.run();
	}
};

GameManager gameManager;
RenderManager gRenderManager;


int main(int argc, const char* argv)
{
	// Start up engine systems in the correct order.
	gameManager.run();
	return 0;
}