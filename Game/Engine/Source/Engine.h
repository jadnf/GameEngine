#pragma once
#include "Engine.h"
#include "Renderer.h"
#include "Audio.h"
#include "Vector2.h"
#include "Input.h"
#include "Particle.h"
#include "Random.h"
#include "EngineTime.h"
#include "MathUtils.h"
#include "Model.h"
#include "Transform.h"

#include <SDL.h>
#include <fmod.hpp>
#include <iostream>

#define RENDERER g_engine.GetRenderer()

class Engine {
public:
	Engine() = default;
	~Engine() = default;

	bool Initialize();
	void Shutdown();

	void Update();

	Renderer& GetRenderer() { return *m_renderer; }
	Input& GetInput() { return *m_input; }
	Audio& GetAudio() { return *m_audio; }

	Time& GetTime() { return *m_time; }

	bool IsQuit() { return quit; }

private:
	bool quit{ false };

	Time* m_time{ nullptr };

	Renderer* m_renderer{ nullptr };
	Input* m_input{ nullptr };
	Audio* m_audio{ nullptr };

};

extern Engine g_engine;

