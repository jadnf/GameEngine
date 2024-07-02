#include "Renderer.h"
#include "Vector2.h"
#include "Input.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <SDL.h>

using namespace std;

int main(int argc, char* argv[])
{
	//create systems
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Engine", 800, 600);

	Input input;
	input.Initialize();

	Vector2 v1{ 400, 300 };
	Vector2 v2{ 700, 500 };

	std::vector<Vector2> points;
	/*for (int i = 0; i < 100; i++) {
		points.push_back(Vector2{rand() % 800, rand() % 600});
	}*/

	bool quit = false;

	while (!quit)
	{
		//input
		//update
		//draw

		//Input
		input.Update();
		if (input.GetKeyDown(SDL_SCANCODE_ESCAPE)) {
			quit = true;
		}
		
		//UPDATE
		Vector2 mousePosition = input.GetMousePosition();
		//std::cout << mousePosition.x << " " << mousePosition.y <<std::endl;

		if (input.GetMouseButtonDown(0) && !input.GetPreviousMouseButtonDown(0)) {
			std::cout << "mouse pressed" << endl;
			points.push_back(mousePosition);
		}
		if (input.GetMouseButtonDown(0) && input.GetPreviousMouseButtonDown(0)) {
			float distance = (points.back() - mousePosition).Length();
			if (distance > 5) {
				points.push_back(mousePosition);
			}
			points.push_back(mousePosition);
		}
		
		/*Vector2 speed{ 0.1f, -0.1f };
		for (Vector2& point : points) {
			point = point + speed;
		}*/
		
		//// clear screen
		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();
		

		renderer.SetColor(100, 100, 100, 100);
		for (int i = 0; points.size() > 1 && i < points.size() - 1; i++) {
			renderer.SetColor(rand() % 256, rand() % 256, rand() % 256, rand() % 256);
			renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
		}


		//SDL_RenderClear(renderer);

		//// draw line
		/*renderer.SetColor(0, 255, 30, 0);
		renderer.DrawLine(0, 0, 800, 300);
		renderer.DrawLine(800, 300, 0, 300);
		renderer.DrawLine(0, 300, 0, 0);
		renderer.SetColor(rand() % 256, rand() % 256, rand() % 256, rand() % 256);
		renderer.DrawLine(rand() % 256, rand() % 256, rand() % 256, rand() % 256);
		renderer.SetColor(rand() % 256, rand() % 256, rand() % 256, rand() % 256);
		renderer.DrawLine(rand() % 256, rand() % 256, rand() % 256, rand() % 256);
		renderer.DrawLine(v1.x, v1.y, v2.x, v2.y);*/

		
		
		//// show screen
		renderer.EndFrame();
	}

	return 0;
}