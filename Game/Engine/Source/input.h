#pragma once
#include "Vector2.h"
#include <vector>
#include <array>

class Input {
public:
	Input() = default;
	~Input() = default;

	bool Initialize();
	void Shutdown();

	void Update();

	bool GetKeyDown(uint8_t key) { return m_keyboardState[key]; }
	bool GetPreviousKeyDown(uint8_t key) { return m_previousKeyboardState[key]; }

	Vector2 GetMousePosition() { return m_mousePosition; }
	bool GetMouseButtonDown(uint8_t button) { return m_mouseButtonState[button]; }
	bool GetPreviousMouseButtonDown(uint8_t button) { return m_previousMouseButtonState[button]; }
private:
	std::vector<uint8_t> m_keyboardState;
	std::vector<uint8_t> m_previousKeyboardState;

	Vector2 m_mousePosition{ 0, 0 };
	std::array<uint8_t, 3> m_mouseButtonState{0,0,0};
	std::array<uint8_t, 3> m_previousMouseButtonState{ 0,0,0 };
};