#include "Header.h"

class GameManager
{
public:
	RenderManager rendManager;
	GameManager()
	{
		std::cout << "Engine created\n";
	}
	~GameManager()
	{
		std::cout << "Engine destroyed\n";
	}

	void run() {	
		std::cout << "RenderManager start\n";
		rendManager.run();
		std::cout << "RenderManager shutdown\n";
	}
};

GameManager gameManager;

int main(int argc, const char* argv)
{
	// Start up engine systems in the correct order.
	std::cout << "Engine startup\n";
	gameManager.run();
	std::cout << "Engine shutdown\n";
	return 0;
}