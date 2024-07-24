#include "ThaGame.h"
#include "Scene.h"
#include "Engine.h"
#include "Player.h"
#include "GameData.h"
#include "Enemy.h"
#include <string>


bool ThaGame::Initialize()
{
	m_scene = new Scene();

	m_font = new Font;
	m_font->Load("Open 24 Display St.ttf", 20);

	m_fontLarge = new Font;
	m_fontLarge->Load("Open 24 Display St.ttf", 75);
	
	m_textLives = new Text(m_font);

	m_textScore = new Text(m_font);

	m_textTitle = new Text(m_fontLarge);

	m_textTitle->Create(g_engine.GetRenderer(), "title", Color{ 0,1,0,0 });
	


    return true;
}

void ThaGame::Shutdown()
{
}

void ThaGame::Update(float dt)
{
	switch (m_state)
	{
	case eState::Title:
		if (m_engine->GetInput().GetKeyDown(SDL_SCANCODE_SPACE)) {
			m_state = eState::StartGame;
		} 
		
		break;
	case eState::StartGame:
		m_score = 0;
		m_state = eState::StartLevel;

		m_textLives->Create(g_engine.GetRenderer(), std::to_string(m_lives), Color{ 0,1,0,0 });
		m_textScore->Create(g_engine.GetRenderer(), std::to_string(m_score), Color{ 0,1,0,0 });
		break;
	case eState::StartLevel:
		{
			Model* model = new Model{ GameData::shipPoints, Color{0,1,0,0} };
			Scene* scene = new Scene();
			Transform transform{ {g_engine.GetRenderer().GetWidth() >> 1,g_engine.GetRenderer().GetHeight() >> 1}, 0, 10 };
			auto player = std::make_unique<Player>(600, transform, model);
			player->SetDamping(1.4f);
			player->SetTag("Player");
			m_scene->AddActor(std::move(player));
		}
		m_spawnTime = 3;
		m_spawnTimer = m_spawnTime;
		
		m_state = eState::Game;
		break;
	case eState::Game:
		m_spawnTimer -= dt;
		if (m_spawnTimer <= 0) {
			m_spawnTime -= 0.2f;
			m_spawnTimer = m_spawnTime;
			Model* enemyModel = new Model{ GameData::shipPoints, Color{1,0,0,0} };
			auto enemy = std::make_unique<Enemy>(1000, Transform{ {g_engine.GetRenderer().GetWidth(), g_engine.GetRenderer().GetWidth()}, 0, 10 }, enemyModel);
			enemy->SetDamping(1.0f);
			enemy->SetTag("Enemy");
			m_scene->AddActor(std::move(enemy));
		}
		break;
	case eState::PlayerDead:
		break;
	case eState::GameOver:
		break;
	default:
		break;
	}
	m_scene->Update(dt);
}

void ThaGame::Draw(Renderer& renderer)
{
	switch (m_state)
	{
	case ThaGame::eState::Title:
		//Draw text
		m_textTitle->Draw(g_engine.GetRenderer(), 40, 20);
		break;

	case ThaGame::eState::Game:
		m_textLives->Draw(g_engine.GetRenderer(), 20, 20);
		m_textLives->Draw(g_engine.GetRenderer(), g_engine.GetRenderer().GetWidth() - 80, 20);

		break;
	case ThaGame::eState::GameOver:
		//Draw text
		break;
	default:
		break;
	}
	m_scene->Draw(renderer);
}
