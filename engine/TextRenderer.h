#pragma once

#include <SDL2/SDL.h>
#include <sdl2/SDL_ttf.h>
#include <string>

namespace Engine
{
	class Renderer;

	/// <remarks xml:lang="ja">
	///	デストラクタでリソース解放を行うため、
	/// ヒープ メモリに保存しないでください
	/// </remarks>
	class TextRenderer {
	public:
		TextRenderer();
		~TextRenderer();

		bool Initialize();
		void Cleanup();

		void DrawText(Renderer& renderer, TTF_Font* font, const std::string& text, int x, int y, SDL_Color color);

	private:
		bool m_is_initialized;
	};
}
