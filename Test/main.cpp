#include <iostream>
#include "Core/Image.h"
#include "Core/Color.h"
#include "Core/Geometry.h"
#include <vector>
#include <string>

#include <chrono>
#include "Core/MemoryPool.h"


using namespace Hebex;
using namespace std::chrono;
int main() {
	/*
	const int width = 1920;
	const int heigh = 1080;
	std::vector<Color> buffer(width * heigh);
	for (int i = 0; i < width * heigh; ++i) {
		buffer[i].b = 0.5f;
	}
	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < heigh; ++y) {
			buffer[y * width + x].r = 1.f * x / width;
			buffer[y * width + x].g = 1.f * y / heigh;
		}
	}

	Image image(width, heigh);
	image.SetBuffer(buffer);
	std::string filename = "test.bmp";
	image.Save(filename, 2.2);
	*/

	std::cerr << Point3f(1, 0, 0) - Point3f(0, 1, 0) << std::endl;
	std::cerr << (Point3f(1, 0, 0) - Point3f(0, 1, 0)).Length() << std::endl;

	struct Node {
		char ch;
		int num[3];
		float i;
	};

	const int iterNum = 1e7;

	auto start = system_clock::now();
	for (int i = 0; i < iterNum; ++i) {
		std::shared_ptr<Node> ptr(new Node());
	}
	auto end = system_clock::now();
	auto duration = duration_cast<milliseconds>(end - start);
	std::cout << duration.count() << "ms" << std::endl;

	start = system_clock::now();
	{
		MemoryPool memoryPool;
		for (int i = 0; i < iterNum; ++i) {
			Node *ptr = ARENA_ALLOC(memoryPool, Node);
		}
	}

	end = system_clock::now();
	duration = duration_cast<milliseconds>(end - start);
	std::cout << duration.count() << "ms" << std::endl;
	system("pause");
	return 0;
}