#include "Engine.h"

Engine g_engine;

bool Engine::Initialize()
{
	m_renderer = std::make_unique<Renderer>();
	m_input = std::make_unique <Input>();
	m_audio = std::make_unique <Audio>();
	m_particleSystem = std::make_unique<ParticleSystem>();

	m_renderer->Initialize();
	m_renderer->CreateWindow("Game Engine", 800, 800);
	m_input->Initialize();
	m_audio->Initialize();

	m_time = std::make_unique <Time>();
	return true;
}

void Engine::Shutdown()
{
	m_renderer->Shutdown();
	m_audio->Shutdown();
	m_input->Shutdown();
}

void Engine::Update()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)){
		if (event.type == SDL_QUIT) {
			quit = true;
		}
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
			quit = true;
		}
	}
	m_time->Tick();
	m_audio->Update();
	m_input->Update();

	m_particleSystem->Update(m_time->GetDeltaTime());
}
