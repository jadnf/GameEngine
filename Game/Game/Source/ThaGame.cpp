#include "ThaGame.h"
#include "Scene.h"
#include "Engine.h"
#include "Player.h"
#include "GameData.h"
#include "Enemy.h"


bool ThaGame::Initialize()
{
	m_scene = new Scene();
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
		break;
	case eState::StartLevel:
		{
			Model* model = new Model{ GameData::shipPoints, Color{0,1,0,0} };
			Scene* scene = new Scene();
			Transform transform{ {g_engine.GetRenderer().GetWidth() >> 1,g_engine.GetRenderer().GetHeight() >> 1}, 0, 10 };
			Player* player = new Player(600, transform, model);
			player->SetDamping(1.4f);
			player->SetTag("Player");
			m_scene->AddActor(player);
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
			auto* enemy = new Enemy(1000, Transform{ {g_engine.GetRenderer().GetWidth(), g_engine.GetRenderer().GetWidth()}, 0, 10 }, enemyModel);
			enemy->SetDamping(1.0f);
			enemy->SetTag("Enemy");
			m_scene->AddActor(enemy);
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
		break;
	case ThaGame::eState::GameOver:
		//Draw text
		break;
	default:
		break;
	}
	//draw score
	//draw lives
	m_scene->Draw(renderer);
}
