#include "Renderer.h"
#include "Vector2.h"
#include "Input.h"
#include "Particle.h"
#include "Random.h"
#include "EngineTime.h"

#include <vector>
#include <iostream>
#include <cstdlib>
#include <SDL.h>

using namespace std;

int main(int argc, char* argv[])
{
	//create systems
	int width = 800;
	int height = 800;

	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Engine", width, height);

	Input input;
	input.Initialize();

	Time time;

	std::vector<Particle> particles;
	

	bool quit = false;

	while (!quit)
	{
		time.Tick();
		//std::cout << time.GetTime() << endl;
		//Input
		
		
		//UPDATE
		input.Update();
		if (input.GetKeyDown(SDL_SCANCODE_ESCAPE)) {
			quit = true;
		}

		Vector2 mousePosition = input.GetMousePosition();
		if (input.GetMouseButtonDown(0) and !input.GetPreviousMouseButtonDown(0)) {
			for (int i = 0; i < random(10, 20); i++) {
				Vector2 velocity = { randomf(-300, 300), randomf(-300, 300) };
				float lifespan = randomf(0.3, 0.5);
				particles.push_back(Particle(mousePosition, velocity, lifespan));
			}
		}

		for (Particle& particle : particles) {
			particle.Update(time.GetDeltaTime());

		}
		


		//// clear screen
		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();

		//Draw shape
		renderer.SetColor(255, 255, 255, 0);
		for (Particle& particle : particles) {
			particle.Draw(renderer);
		}

		renderer.EndFrame();
	}

	return 0;
}