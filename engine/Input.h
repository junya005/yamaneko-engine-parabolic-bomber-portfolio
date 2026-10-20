#pragma once
#include <SDL2/SDL.h>
#include <unordered_map>

namespace Engine {
	class Input {
	public:
		Input();
		~Input();

		void BeginFrame();

		void ProcessEvent(const SDL_Event& e);

		bool GetKey(SDL_Scancode scancode) const;

		bool GetKeyDown(SDL_KeyCode keycode) const;
	
	private:
		std::unordered_map<SDL_Keycode, bool> m_key_downs;

		const Uint8* m_keyboard_state;
	};
}
