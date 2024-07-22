#pragma once
#include "Game.h"
#include "Text.h"
#include "Font.h"

class ThaGame : public Game {
public:
	enum class eState {
		Title,
		StartGame,
		StartLevel,
		Game,
		PlayerDead,
		GameOver
	};
public:
	ThaGame(Engine* engine) : Game{ engine } {
	
	};

	bool Initialize() override;
	void Shutdown() override;
	void Update(float dt) override;
	void Draw(Renderer& renderer) override;

private:
	eState m_state{ eState::Title };

	float m_lives{ 0 };
	float m_spawnTimer{ 0 };
	float m_spawnTime{ 0 };

	Font* m_font { nullptr };
	Font* m_fontLarge{ nullptr };

	Text* m_textScore{ nullptr };
	Text* m_textLives{ nullptr };
	Text* m_textTitle{ nullptr };


	
};