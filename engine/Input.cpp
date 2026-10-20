#include "Input.h"

namespace Engine
{
	Input::Input() : m_keyboard_state(nullptr) {
		m_keyboard_state = SDL_GetKeyboardState(nullptr);
	}

	Input::~Input() {

	}

	void Input::BeginFrame() {
		m_key_downs.clear();
	}

	void Input::ProcessEvent(const SDL_Event& e) {
		if (e.type == SDL_KEYDOWN) {
			if (e.key.repeat == 0) {
				m_key_downs[e.key.keysym.sym] = true;
			}
		}
	}

	bool Input::GetKey(SDL_Scancode scancode) const {
		if (m_keyboard_state) {
			return m_keyboard_state[scancode] != 0;
		}
		return false;
	}

	bool Input::GetKeyDown(SDL_KeyCode keycode) const {
		auto it = m_key_downs.find(keycode);
		if (it != m_key_downs.end()) {
			return it->second;
		}
		return false;
	}
}
