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
	
	//Testing code for Math Library
	Vector3D vec1 = Vector3D(1, 3, -2);
	Vector3D vec2 = Vector3D(5, 1, 7);
	Point3D pos1 = Point3D(1, 2, 3);
	Point3D pos2 = Point3D(4, 5, 7);

	std::cout << vec1.Dot(vec2) << "\n";

	Vector3D vec3 = vec1 + vec2;
	std::cout << vec3.x << "," << vec3.y << "," << vec3.z << "," << vec3.w << "\n";
	vec3.add(vec1);
	std::cout << vec3.x << "," << vec3.y << "," << vec3.z << "," << vec3.w << "\n";
	vec3.scale(2, 2, 2);
	std::cout << vec3.x << "," << vec3.y << "," << vec3.z << "," << vec3.w << "\n";

	Vector3D vec4 = vec1.Cross(vec2);
	std::cout << vec4.x << "," << vec4.y << "," << vec4.z << "," << vec4.w << "\n";

	std::cout << vec1.Magnitude() << "\n";
	vec1.Normalize();
	std::cout << vec1.x << "," << vec1.y << "," << vec1.z << "," << vec3.w << "\n";

	Vector3D vec5 = pos2 - pos1;
	std::cout << vec5.x << "," << vec5.y << "," << vec5.z << "," << vec5.w << "\n";
	Point3D pos3 = pos1 + vec2;
	std::cout << pos3.x << "," << pos3.y << "," << pos3.z << "," << pos3.w << "\n";


	//Testing code for Memory Allocation

	std::cout << "Engine startup\n";
	gameManager.run();
	std::cout << "Engine shutdown\n";
	return 0;
}