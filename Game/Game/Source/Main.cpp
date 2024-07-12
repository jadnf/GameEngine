#include "Renderer.h"
#include "Vector2.h"
#include "Input.h"
#include "Particle.h"
#include "Random.h"
#include "EngineTime.h"
#include "MathUtils.h"
#include "Model.h"
#include "Transform.h"

#include <vector>
#include <iostream>
#include <cstdlib>
#include <SDL.h>
#include <fmod.hpp>

using namespace std;

int main(int argc, char* argv[])
{
	//create systems
	int width = 800;
	int height = 800;

	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Engine", width, height);

	// create audio system
	FMOD::System* audio;
	FMOD::System_Create(&audio);

	void* extradriverdata = nullptr;
	audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

	FMOD::Sound* sound = nullptr;
	audio->createSound("test.wav", FMOD_DEFAULT, 0, &sound);

	audio->playSound(sound, 0, false, nullptr);

	std::vector<FMOD::Sound*> sounds;
	
	audio->createSound("bass.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	audio->createSound("snare.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	audio->createSound("clap.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);
	
	audio->createSound("close-hat.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	audio->createSound("open-hat.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	audio->createSound("cowbell.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	

	Input input;
	input.Initialize();

	Time time;

	std::vector<Particle> particles;
	float offset = 0;

	std::vector<Vector2> points;
	points.push_back(Vector2{ 0.0F,1.5f });
	points.push_back(Vector2{ 1.0F,0.5f });
	points.push_back(Vector2{ 1.5F,0.5f });
	points.push_back(Vector2{ 1.5F,0.5f });
	points.push_back(Vector2{ 2.5F,0.0f });
	points.push_back(Vector2{ 1.5F,-0.5f });
	points.push_back(Vector2{ 1.0F,-0.5f });
	points.push_back(Vector2{ 0.0F,-1.5f });
	points.push_back(Vector2{ 0.5F,0.0f });
	points.push_back(Vector2{ 0.0F,1.5f });
	
	
	Model model{ points, Color{0,1,0,0} };

	Transform transform{ {renderer.GetWidth() >> 1,renderer.GetHeight() >> 1}, 0, 10};

	bool quit = false;

	while (!quit)
	{
		time.Tick();
		//Input
		input.Update();
		if (input.GetKeyDown(SDL_SCANCODE_ESCAPE)) {
			quit = true;
		}
		float thrust = 0;
		if (input.GetKeyDown(SDL_SCANCODE_LEFT)) transform.rotation -= Math::DegToRad(100) * time.GetDeltaTime();
		if (input.GetKeyDown(SDL_SCANCODE_RIGHT)) transform.rotation += Math::DegToRad(100) * time.GetDeltaTime();
		if (input.GetKeyDown(SDL_SCANCODE_DOWN)) thrust = -400;
		if (input.GetKeyDown(SDL_SCANCODE_UP)) thrust = 400;

		Vector2 velocity = Vector2{ thrust,0.0f }.Rotate(transform.rotation);
		transform.position += velocity * time.GetDeltaTime();
		transform.position.x = Math::Wrap(transform.position.x, (float)renderer.GetWidth());
		transform.position.y = Math::Wrap(transform.position.y, (float)renderer.GetHeight());
		//transform.rotation = velocity.Angle();

		Vector2 mousePosition = input.GetMousePosition();
		if (input.GetMouseButtonDown(0) and !input.GetPreviousMouseButtonDown(0)) {
			for (int i = 0; i < random(10, 600); i++) {
				//Vector2 velocity = randomOnUnitCircle();
				//float lifespan = randomf(0.3, 0.5);
				particles.push_back(Particle(mousePosition, randomOnUnitCircle() * random(10,400), randomf(0.01f,0.7f), random(0,255), random(0, 255), random(0, 255), 0));
			}
		}

		for (Particle& particle : particles) {
			particle.Update(time.GetDeltaTime());

		}
		


		//// clear screen
		renderer.SetColor(0, 0, 0, 0);
		
		renderer.BeginFrame();

		/*renderer.SetColor(255, 255, 255, 0);
		float radius = 80.0f;
		offset += (360 * time.GetDeltaTime());
		for (float angle = 0; angle < 360; angle += 360 / 120) {
			float x = Math::Cos(Math::DegToRad(angle + offset)) * Math::Sin((offset + angle) * 0.11f) * radius;
			float y = Math::Sin(Math::DegToRad(angle + offset)) * Math::Sin((offset + angle) * 0.032199f) * radius;

			renderer.SetColor(random(0, 255), random(0, 255), random(0, 255), 0);
			renderer.DrawRect(400 + x, 400 + y, 4.0f, 4.0f);
		}*/

		//Draw particles
		renderer.SetColor(255, 255, 255, 0);
		for (Particle& particle : particles) {
			particle.Draw(renderer);
		}
		//sounds 
		if (input.GetKeyDown(SDL_SCANCODE_Q) && !input.GetPreviousKeyDown(SDL_SCANCODE_Q)) {
			audio->playSound(sounds[0], 0, false, nullptr);
		}
		if (input.GetKeyDown(SDL_SCANCODE_W) && !input.GetPreviousKeyDown(SDL_SCANCODE_W)) {
			audio->playSound(sounds[1], 0, false, nullptr);
		}
		if (input.GetKeyDown(SDL_SCANCODE_E) && !input.GetPreviousKeyDown(SDL_SCANCODE_E)) {
			audio->playSound(sounds[4], 0, false, nullptr);
		}
		if (input.GetKeyDown(SDL_SCANCODE_T) && !input.GetPreviousKeyDown(SDL_SCANCODE_S)) {
			for (int i = 0; i < random(20, 583) - 1; i++) {
				audio->playSound(sounds[random(0,6)], 0, false, nullptr);
			}
			
		}

		renderer.SetColor(255, 255, 255, 0);
		model.Draw(renderer, transform);

		renderer.EndFrame();
		audio->update();
	}

	return 0;
}