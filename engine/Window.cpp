#include "Window.h"

namespace Engine
{
	Window::Window() : m_window(nullptr), m_width(0), m_height(0) {

	}

	Window::~Window() {
		Cleanup();
	}

	bool Window::Initialize(const std::string& title, int width, int height) {
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
			SDL_Log("Failed to initialization.: %s", SDL_GetError());
			return false;
		}

		m_width = width;
		m_height = height;

		m_window = SDL_CreateWindow(
			title.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			m_width,
			m_height,
			0
		);

		if (m_window == nullptr) {
			SDL_Log("Failed to window initialization.: %s", SDL_GetError());
			return false;
		}

		return true;
	}

	void Window::Cleanup() {
		if (m_window) {
			SDL_DestroyWindow(m_window);
			m_window = nullptr;
		}

		SDL_Quit();
	}
}

