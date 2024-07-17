#include "Engine.h"
#include "Player.h"
#include "Scene.h"
#include "Enemy.h"

#include <vector>
#include <iostream>
#include <cstdlib>
#include <string>


using namespace std;

int main(int argc, char* argv[])
{
	g_engine.Initialize();
	//create systems
	int width = 800;
	int height = 800;

	Time time;
	

	// create audio system
	g_engine.GetAudio().AddSound("bass.wav");
	g_engine.GetAudio().AddSound("snare.wav");
	g_engine.GetAudio().AddSound("clap.wav");
	g_engine.GetAudio().AddSound("close-hat.wav");
	g_engine.GetAudio().AddSound("open-hat.wav");
	g_engine.GetAudio().AddSound("cowbell.wav");
	
	



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
	
	
	Model* model = new Model{ points, Color{0,1,0,0} };
	Scene* scene = new Scene();
	Transform transform{ {g_engine.GetRenderer().GetWidth() >> 1,g_engine.GetRenderer().GetHeight() >> 1}, 0, 10};
	Player* player = new Player(600, transform, model);
	player->SetDamping(1.4f);
	player->SetTag("Player");
	scene->AddActor(player);

	Model* enemyModel = new Model{ points, Color{1,0,0,0} };
	auto* enemy = new Enemy(10000, Transform{ {g_engine.GetRenderer().GetWidth(), g_engine.GetRenderer().GetWidth()}, 0, 10}, enemyModel);
	enemy->SetDamping(1.0f);
	enemy->SetTag("Enemy");
	scene->AddActor(enemy);



	float spawnTimer = 2;

	
	
	//main loop
	bool quit = false;
	while (!quit)
	{
		time.Tick();
		//Input
		g_engine.GetInput().Update();
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_ESCAPE)) {
			quit = true;
		}
	
		Vector2 mousePosition = g_engine.GetInput().GetMousePosition();
		if (g_engine.GetInput().GetMouseButtonDown(0) and !g_engine.GetInput().GetPreviousMouseButtonDown(0)) {
			for (int i = 0; i < random(10, 600); i++) {
				//Vector2 velocity = randomOnUnitCircle();
				//float lifespan = randomf(0.3, 0.5);
				particles.push_back(Particle(mousePosition, randomOnUnitCircle() * random(10,400), randomf(0.01f,0.7f), random(0,255), random(0, 255), random(0, 255), 0));
			}
		}

		spawnTimer -= time.GetDeltaTime();
		if (spawnTimer <= 0) {
			Model* enemyModel = new Model{ points, Color{1,0,0,0} };
			auto* enemy = new Enemy(10000, Transform{ {g_engine.GetRenderer().GetWidth(), g_engine.GetRenderer().GetWidth()}, 0, 10 }, enemyModel);
			enemy->SetDamping(1.0f);
			enemy->SetTag("Enemy");
			scene->AddActor(enemy);
			spawnTimer = 1;
		}

		for (Particle& particle : particles) {
			particle.Update(time.GetDeltaTime());

		}
		scene->Update(time.GetDeltaTime());
		scene->Draw(g_engine.GetRenderer());
		


		//// clear screen
		g_engine.GetRenderer().SetColor(0, 0, 0, 0);
		
		g_engine.GetRenderer().BeginFrame();

		//Draw particles
		g_engine.GetRenderer().SetColor(255, 255, 255, 0);
		for (Particle& particle : particles) {
			particle.Draw(g_engine.GetRenderer());
		}

		g_engine.GetRenderer().SetColor(255, 255, 255, 0);
		player->Draw(g_engine.GetRenderer());
		scene->Draw(g_engine.GetRenderer());

		g_engine.GetRenderer().EndFrame();
		//sounds 
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_Q) && !g_engine.GetInput().GetPreviousKeyDown(SDL_SCANCODE_Q)) {
			g_engine.GetAudio().PlaySound("bass.wav");
		}
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_W) && !g_engine.GetInput().GetPreviousKeyDown(SDL_SCANCODE_W)) {
			g_engine.GetAudio().PlaySound("snare.wav");
		}
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_E) && !g_engine.GetInput().GetPreviousKeyDown(SDL_SCANCODE_E)) {
			g_engine.GetAudio().PlaySound("cowbell.wav");
		}
		
		g_engine.GetAudio().Update();
	}

	return 0;
}