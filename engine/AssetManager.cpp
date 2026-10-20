#include "AssetManager.h"
#include "Renderer.h"

namespace Engine {
	AssetManager::AssetManager(){

	}

	AssetManager::~AssetManager() {
		Cleanup();
	}

	SDL_Texture* AssetManager::LoadTexture(Renderer& renderer, const std::string& file_path) {
		auto it = m_textures.find(file_path);
		if (it != m_textures.end()) {
			return it->second;
		}
		
		SDL_Surface* surface = IMG_Load(file_path.c_str());
		if (!surface) {
			SDL_Log("画像の読み込みに失敗 %s: %s", file_path.c_str(), SDL_GetError());
			return nullptr;
		}

		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer.GetSDLRenderer(), surface);
		SDL_FreeSurface(surface);

		if (!texture) {
			SDL_Log("テクスチャの作成に失敗 %s: %s", file_path.c_str(), SDL_GetError());
			return nullptr;
		}
		
		m_textures[file_path] = texture;

		return texture;
	}

	TTF_Font* AssetManager::LoadFont(const std::string& file_path, int font_size) {
		std::string key = file_path + "_" + std::to_string(font_size);

		auto it = m_fonts.find(file_path);
		if (it != m_fonts.end()) {
			return it->second;
		}

		TTF_Font* font = TTF_OpenFont(file_path.c_str(), font_size);
		if (!font) {
			SDL_Log("Font Load Error %s: %s", file_path.c_str(), SDL_GetError());
		}
		return font;
	}

	void AssetManager::Cleanup() {
		for (auto pair : m_textures) {
			if (pair.second) {
				SDL_DestroyTexture(pair.second);
			}
		}

		m_textures.clear();

		for (auto pair : m_fonts) {
			if (pair.second){
				TTF_CloseFont(pair.second);
			}
		}

		m_fonts.clear();
	}
}