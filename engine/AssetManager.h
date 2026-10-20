#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <sdl2/SDL_ttf.h>
#include <string>
#include <unordered_map>

namespace Engine {
	class Renderer;

	class AssetManager {
	public:
		AssetManager();
		~AssetManager();

		SDL_Texture* LoadTexture(Renderer& renderer, const std::string& file_path);

		TTF_Font* LoadFont(const std::string& file_path, int font_size);

		void Cleanup();

	private:
		std::unordered_map<std::string, SDL_Texture*> m_textures;
		std::unordered_map<std::string, TTF_Font*> m_fonts;
	};
}
